/* This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include <string.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <gtkdatabox.h>
#include <gtkdatabox_points.h>
#include <gtkdatabox_ruler.h>
#include <math.h>

#define POINTS 10000
#define YMAX   1.2
#define YMIN   -YMAX
//TIMEBASE in ms
#define TIMEBASE 1000
#define TIME(time)  time.tv_sec + ((gdouble) time.tv_usec / 1000000); 

enum hscales { 
    ADJUST_VISIBLE_LIMITS, 
    ADJUST_PERIOD_LENGTH
};
		
static gfloat *X;
static gfloat *Y;
static GTimeVal nowval, pastval;
static gdouble length_of_period;
GtkWidget *labelFPS;


gdouble function_to_plot(gdouble time) {
    return sin (2 * G_PI / length_of_period * time);
}


static gboolean hscale_generic_cb(GtkRange *range, GtkWidget *box) {
    GtkAdjustment *adjust;
    gdouble lower, upper, value, dest;
    enum hscales h;

    value = gtk_range_get_value(range);
    adjust = gtk_range_get_adjustment(range);

    lower = gtk_adjustment_get_lower(adjust);
    upper = gtk_adjustment_get_upper(adjust);

    if(value <= lower) {
	dest = lower;
    }
    else if(value >= upper) {
	dest = upper;
    }
    else {
	dest = value;
    }

    h = (enum hscales) g_object_get_data(G_OBJECT(range), "id");

    switch( h ) {

	case ADJUST_VISIBLE_LIMITS:
	    gtk_databox_set_visible_limits(GTK_DATABOX(box), 0, dest, YMIN, YMAX);
	    break;
	case ADJUST_PERIOD_LENGTH:
	    length_of_period = dest;
	    break;

    }
    
    return FALSE;
}

static gboolean update_graph (GtkWidget *box)
{
   gdouble past, now;
   static gdouble carry_over = 0;
   gint time_in_ms, i;
   gchar *str;
   void *tmp;

   past = TIME(pastval);
   
   g_get_current_time(&nowval);
   pastval = nowval;
   now = TIME(nowval);

   time_in_ms = (gint) ((now-past) * TIMEBASE);
   carry_over += (now-past) * TIMEBASE - (gdouble) time_in_ms ;

   /*--------------------------------------------------------
    * don't loose time
    *------------------------------------------------------*/
   if( (gint) carry_over >= 1) {
	time_in_ms += (gint) carry_over;
	carry_over = carry_over - (gint) carry_over;
    }

    str =  g_strdup_printf("Fps: %f", 1/(now-past));
    gtk_label_set_label(GTK_LABEL(labelFPS), str);
    g_free(str);

    /*--------------------------------------------------------
     * The below case is very unprobable 
     *------------------------------------------------------*/
    if(time_in_ms >= POINTS)
	time_in_ms = POINTS;

  
    /*--------------------------------------------------------
     * shift current data of Y by time_in_ms to the right
     *------------------------------------------------------*/
    tmp = g_memdup(Y, sizeof(gfloat)*(POINTS-time_in_ms));
    g_memmove((Y+time_in_ms), tmp, sizeof(gfloat)*(POINTS-time_in_ms));
    g_free(tmp);

    /*--------------------------------------------------------
     * write all points at the beginning of Y
     * which belong to the previously elapsed time
     *------------------------------------------------------*/
    for(i=time_in_ms; i>=0; i--) {
        Y[i] = function_to_plot(now-((gdouble) i/TIMEBASE ));
    }

   gtk_widget_queue_draw (GTK_WIDGET(box));

   return TRUE;
}

/*----------------------------------------------------------------
 *  databox basics
 *----------------------------------------------------------------*/

static void
create_basics (void)
{
   GtkWidget *window = NULL;
   GtkWidget *vbox;
   GtkWidget *hbox;
   GtkWidget *label;
   GtkWidget *close_button;
   GtkWidget *box;
   GtkWidget *separator;
   GtkWidget *table;
   GtkWidget *hs_adj_visible_limits;
   GtkWidget *hs_adj_period;
   GtkDataboxGraph *graph;
   GdkColor color;
   gint i;

   /* We define some data */
   X = g_new0 (gfloat, POINTS);
   Y = g_new0 (gfloat, POINTS);

   for (i = 0; i < POINTS; i++) {
      X[i] = i;
   }

   window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
   gtk_widget_set_size_request (window, 500, 500);

   g_signal_connect (GTK_OBJECT (window), "destroy",
		     G_CALLBACK (gtk_main_quit), NULL);

   gtk_window_set_title (GTK_WINDOW (window), "GtkDatabox: plot function in real-time");
   gtk_container_set_border_width (GTK_CONTAINER (window), 0);

   vbox = gtk_vbox_new (FALSE, 0);
   gtk_container_add (GTK_CONTAINER (window), vbox);

   labelFPS = gtk_label_new("[---]");
   gtk_box_pack_start(GTK_BOX(vbox), labelFPS, FALSE, TRUE, 20);

   /* -----------------------------------------------------------------
    * This is all you need:
    * -----------------------------------------------------------------
    */

   /* Create the GtkDatabox widget */
   gtk_databox_create_box_with_scrollbars_and_rulers (&box, &table,
						      TRUE, FALSE, TRUE, TRUE);

   /* Put it somewhere */
   gtk_box_pack_start (GTK_BOX (vbox), table, TRUE, TRUE, 0);

   /* Add your data data in some color */
   color.red = 0xffff;
   color.green = 0xffff;
   color.blue = 0xffff;
   gtk_widget_modify_bg (box, GTK_STATE_NORMAL, &color);

   /* Add your data data in some color */
   color.red = 0;
   color.green = 0;
   color.blue = 0;

   graph = (GtkDataboxGraph *) gtk_databox_lines_new (POINTS, X, Y, &color, 1);
   gtk_databox_graph_add (GTK_DATABOX (box), graph);

   gtk_databox_set_total_limits (GTK_DATABOX (box), 0, POINTS, YMIN, YMAX);

    /* -----------------------------------------------------------------
    * Done :-)
    * -----------------------------------------------------------------
    */

   separator = gtk_hseparator_new ();
   gtk_box_pack_start (GTK_BOX (vbox), separator, FALSE, TRUE, 0);

    /*--------------------------------------------------------
     * Create hscale widget to adjust the visible limits of
     * the databox
     *------------------------------------------------------*/

   hbox = gtk_hbox_new(TRUE, 0);

   label = gtk_label_new("section of time axis in ms:");

   hs_adj_visible_limits = gtk_hscale_new_with_range(POINTS/10, POINTS, 1);
   gtk_range_set_update_policy(GTK_RANGE(hs_adj_visible_limits), GTK_UPDATE_DISCONTINUOUS);
   gtk_scale_set_value_pos(GTK_SCALE(hs_adj_visible_limits), GTK_POS_RIGHT);
   g_object_set_data(G_OBJECT(hs_adj_visible_limits), "id", (gpointer) ADJUST_VISIBLE_LIMITS);
   g_signal_connect(GTK_OBJECT(hs_adj_visible_limits), "value-changed", G_CALLBACK(hscale_generic_cb), box);
   gtk_range_set_value(GTK_RANGE(hs_adj_visible_limits), POINTS);
   gtk_box_pack_start(GTK_BOX(hbox), label, TRUE, TRUE, 0);
   gtk_box_pack_start(GTK_BOX(hbox), hs_adj_visible_limits, TRUE, TRUE, 0);
   gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

   separator = gtk_hseparator_new ();
   gtk_box_pack_start(GTK_BOX(vbox), separator, FALSE, FALSE, 0);

    /*--------------------------------------------------------
    * Create hscale widget to adjust the length of period of
    * the sinus function
    *------------------------------------------------------*/
   
   hbox = gtk_hbox_new(TRUE, 0);
    
   label = gtk_label_new("period of plotted sinus in s:");
   
   hs_adj_period = gtk_hscale_new_with_range(0.2, 10, 0.2);
   gtk_scale_set_value_pos(GTK_SCALE(hs_adj_period), GTK_POS_RIGHT);
   gtk_range_set_update_policy(GTK_RANGE(hs_adj_period), GTK_UPDATE_DISCONTINUOUS);
   g_object_set_data(G_OBJECT(hs_adj_period), "id", (gpointer) ADJUST_PERIOD_LENGTH);
   g_signal_connect(GTK_OBJECT(hs_adj_period), "value-changed", G_CALLBACK(hscale_generic_cb), box);
   gtk_range_set_value(GTK_RANGE(hs_adj_period), 2);

   gtk_box_pack_start(GTK_BOX(hbox), label, TRUE, TRUE, 0);
   gtk_box_pack_start(GTK_BOX(hbox), hs_adj_period, TRUE, TRUE, 0);
   gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    /*--------------------------------------------------------
     * Create button widget that connects to cb which
     * quits the program
     *------------------------------------------------------*/

   close_button = gtk_button_new_with_label ("close");
   g_signal_connect_swapped (GTK_OBJECT (close_button), "clicked",
			     G_CALLBACK (gtk_main_quit), GTK_OBJECT (box));
   
   gtk_box_pack_start (GTK_BOX (vbox), close_button, FALSE, FALSE, 0);

    /*--------------------------------------------------------
    * set function update_graph to be called whenever 
    * the program is idle
    *------------------------------------------------------*/

   g_idle_add_full(G_PRIORITY_HIGH_IDLE+21, (GSourceFunc) update_graph, (gpointer) window, NULL);
   gtk_widget_show_all (window);
   gdk_window_set_cursor (box->window, gdk_cursor_new (GDK_CROSS));

}
/*
gint
main (gint argc, char *argv[])
{
   gtk_init (&argc, &argv);

   create_basics ();
*/
   /*--------------------------------------------------------
    * save timestamp to calculate the first time interval 
    * in update_graph
    *------------------------------------------------------*/
/*
   g_get_current_time(&pastval);

   gtk_main ();

   return 0;
}*/
