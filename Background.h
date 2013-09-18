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
#define POINTS 1000

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



void init_company();
Company get_Company_by_name(const char* name);
Company* get_Company(int n);

bool update();
void Buy(GtkWidget *widget, gpointer data);
void Sell(GtkWidget *widget, gpointer data);

float Value_midrange(Company* pCompany);
float Statistics(Company* pCompany);

void Buy_action(char* value);
void Sell_action(char* value);

char* float2Text(float found);
char* type2Text(society val);
float text2float(char* txt);

#endif