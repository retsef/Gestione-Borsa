/* 
 * File:   Gtk_Widget.h
 * Author: roberto
 *
 * Created on 3 agosto 2013, 2.21
 */
#include "Background.h"
#include <stdbool.h>
#include <gtk/gtk.h>

GtkWidget * create_notebook_label(const gchar *text, GtkNotebook *notebook, bool cloosable, int page);
static void cb_close_tab(GtkButton *button, GtkNotebook *notebook);
GdkPixbuf * create_pixbuf(const gchar * filename);
GtkWidget * create_graph_with_rules(gfloat *x, gfloat *y, int graph_lenght);
GtkWidget * create_company_frame_graph(Company* Company_n, GtkWidget *Company_graph);
GtkWidget * create_company_frame(Company* Company_n);
void create_company_tab(GtkButton *button, GtkWidget *array[]);
