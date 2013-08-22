/* 
 * File:   Background.h
 * Author: roberto
 *
 * Created on 6 agosto 2013, 13.10
 */
#include <stdlib.h>
//fa un alias tra la struttura _Comapny a Comany (puntatore opaco)
typedef struct _Company Company;

void init_company();
Company *getCompany(int n);
void update();

char* type2Text(society val);