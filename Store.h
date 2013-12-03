/* 
 * File:   Store.h
 * Author: roberto
 *
 * Created on 6 ottobre 2013, 18.27
 */

#ifndef STORE_H
#define	STORE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <pthread.h>
#include <math.h>
#include <tgmath.h>

#include <gtk/gtk.h>
#define POINTS 1000

extern pthread_mutex_t lock;

typedef float Money;

typedef struct{
    Money wallet;
}User;

typedef struct {
    GtkWidget *button;
    GtkWidget *label;
    GtkWidget *graph;
    GtkWidget *frame;
    GtkNotebook *notebook;
}Company_exposer;

typedef struct {
    GtkWidget *container;
    GtkWidget *template;
    GtkWidget *name;
    GtkWidget *type;
    GtkWidget *found;
    GtkWidget *point;
    GtkWidget *midvalue;
    GtkWidget *max;
    GtkWidget *min;
    GtkWidget *stats_found;
    GtkWidget *stats_point;
}Company_frame_content;

typedef enum {spa,sapa,srl,srls} society;
typedef struct Action Action;

typedef struct{
    char* name;
    society type;
    float midvalue[POINTS];
    float stats_found;
    float stats_point;
    Money found;
    Money pre_point;
    Money point;
    float max;
    float min;
    float x[POINTS];
    float y[POINTS];
    int id;
    int idle;
    pthread_t thread;
    //viene mantenuto il legame tra la company e il suo contenuto su GUI
    Company_frame_content* frame_content;
    Action* action;
}Company;

typedef struct {
    GtkWidget *dialog;
    GtkWidget *label;
    GtkWidget *input;
    GtkWidget *bancomat;
    
    GtkWidget *hbox;
    GtkWidget *ok;
    GtkWidget *cancel;
    gpointer window;
}Action_dialog;

typedef struct{
    GtkWidget *frame;
    GtkWidget *container;
    GtkWidget *template;
    
    GtkWidget *name;
    GtkWidget *type;
    GtkWidget *found;
    GtkWidget *stats;
    GtkWidget *own_action;
    GtkWidget *own_stats;
}Action_content;

struct Action{
    Company* company;
    Action_content* content;
    Action_dialog* dialog;
    User* actionist;
    Money found;
    Money pre_found;
    float stats;
};

typedef struct{
    GtkWidget *frame_action;
    GtkWidget *action_container;
    GtkWidget *frame_home;
    GtkWidget *home_container;
    
    GtkWidget *template;
    GtkWidget *home_found;
    
    pthread_t thread;
    int idle;
}Actionist_Profile;

Company* new_Company();
void destroy_Company(Company* pCompany);
//void init_all_Company();
void INIT_ALL(GtkNotebook* notebook, GtkFixed* Container, GtkWidget* window);
void *update_graph_value(void *ptr);

Company* get_Company(int index);
Action* get_Action(int index);
Action* get_Action_from_Company(Company* cmp);
Company_exposer* get_Company_exposer(int index);


User* new_User(Money bank);
User* get_User();
void destroy_User(User* usr);
void init_User(Money wallet);

Action* new_Action(Company* pCompany, User* pActionist);
//void create_Action(Action* act);
void destroy_Action(Action* act);

bool Can_Pay(Action* act, char* str);
bool Can_Sell(Action* act, char* str);

void Pay(Action* act, char* str);
void Sale(Action* act, char* str);

char* type2text(society val);
char* float2text(float value);
bool is_a_float(char* str);
float char2float(char* chr);
float middle_value(float arr[], int ln);
float stats_float_value(float arr[], int ln);
float stats_point_value(float pre_point, float point);
float stats_action(float pre_found, float found);

float max_value(float arr[], int ln);
float min_value(float arr[], int ln);

void Buy_action(Action* act);
void Sell_action(Action* act);

#endif	/* STORE_H */
