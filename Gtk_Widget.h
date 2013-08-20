/* 
 * File:   Gtk_Widget.h
 * Author: roberto
 *
 * Created on 3 agosto 2013, 2.21
 */

#include <stdbool.h>
#include <gtk/gtk.h>
#include <gtkdatabox.h>
#include <gtkdatabox_ruler.h>
#include <gtkdatabox_lines.h>

GtkWidget * create_notebook_label(const gchar *text, GtkNotebook *notebook, bool cloosable, int page);
static void cb_close_tab(GtkButton *button, GtkNotebook *notebook);
GdkPixbuf * create_pixbuf(const gchar * filename);
GtkWidget * create_graph_with_rules(gfloat *x, gfloat *y, int graph_lenght);
void * create_company_tab(GtkWidget *notebook, GtkWidget *label, GtkWidget *button, GtkWidget *Company);
