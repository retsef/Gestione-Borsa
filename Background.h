/* 
 * File:   Background.h
 * Author: roberto
 *
 * Created on 6 agosto 2013, 13.10
 */
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdbool.h>
#define POINTS 100

typedef enum {spa,sapa,srl,srls} society;

typedef float Money;

typedef struct{
    char* name;
    society type;
    float found;
    float x[POINTS];
    float y[POINTS];
}Company;

typedef struct{
    float action;
    Money wallet;
}User;



typedef struct{
    GtkWidget *label;
    GtkWidget *notebook;
    GtkWidget *frame;
}Data_notebook;

void init_company();
Company get_Company_by_name(const char* name);
Company* get_Company(int n);

bool update();
void Buy(GtkButton *button);
void Sell(GtkButton *button);

char* found2Text(float found);
char* type2Text(society val);

#endif