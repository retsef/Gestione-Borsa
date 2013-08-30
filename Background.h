/* 
 * File:   Background.h
 * Author: roberto
 *
 * Created on 6 agosto 2013, 13.10
 */
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <stdlib.h>
#include <stdbool.h>
#define POINTS 100

typedef enum {spa,sapa,srl,srls} society;

typedef struct{
    char* name;
    society type;
    float found;
    float x[POINTS];
    float y[POINTS];
}Company;

//typedef struct Company Company;

void init_company();
Company get_Company_by_name(const char* name);
Company get_Company(int n);
bool update();

char* found2Text(float found);
char* type2Text(society val);

#endif