/* 
 * File:   Background.h
 * Author: roberto
 *
 * Created on 6 agosto 2013, 13.10
 */
#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <stdlib.h>

typedef enum {spa,sapa,srl,srls} society;

typedef struct{
    char* name;
    society type;
    float found;
    float x[15];
    float y[15];
}Company;

//typedef struct Company Company;

void init_company();
Company get_Company_by_name(const char* name);
Company get_Company(int n);
void update();

char* type2Text(society val);

#endif