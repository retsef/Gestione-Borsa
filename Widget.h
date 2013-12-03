/* 
 * File:   Widget.h
 * Author: roberto
 *
 * Created on 6 ottobre 2013, 18.27
 */

#ifndef WIDGET_H
#define	WIDGET_H

#include <stdbool.h>
#include <string.h>

#include <gtkdatabox.h>
#include <gtkdatabox_points.h>
#include <gtkdatabox_lines.h>

#include "Store.h"

Company_exposer* new_Company_exposer();
void destroy_Company_exposer(Company_exposer* cmp_exp);

Company_frame_content* new_Company_frame_content();
void destroy_Company_frame_content(Company_frame_content* cmp_frm);

Action_dialog* new_Action_dialog();
void destroy_Action_dialog(Action_dialog* act);

Action_content* new_Action_content(Company* pCompany);
void destroy_Action_content(Action_content* act_cnt);

Actionist_Profile* new_Actionist_profile(User* pActionist, GtkFixed* Container);
void destroy_Actionist_profile(Actionist_Profile* act_prf);

//void init_all_Action(GtkFixed* Container);
//void init_all_Company_exposer(GtkNotebook* notebook, GtkWidget* window);

void show_about(GtkWidget *widget, gpointer data);
GdkPixbuf *create_pixbuf(const gchar *filename);

GtkWidget *create_notebook_label(const char *text, GtkNotebook *notebook, bool cloosable, int page);
static void cb_close_tab(GtkButton *button, GtkNotebook *notebook);

GtkWidget * create_graph_with_rules(gfloat *x, gfloat *y, gfloat *mid, int graph_lenght);
GtkWidget *create_company_frame_graph(Company* Company_n, GtkWidget *Company_graph, gpointer window);
void create_company_tab(GtkButton *button, Company_exposer *cmp_exp);

bool update_graph_draw(GtkWidget* box);
bool update_graph_scale(GtkWidget* databox);
void *update_graph_value(void *ptr);
void *update_actionist_profile_draw(void *act);

void Buy(GtkButton *button, Action* act);
void Sell(GtkButton *button, Action* act);
void exit_Action(Action_dialog* act);

void exit_Application();

#endif	/* WIDGET_H */
