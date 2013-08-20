/* 
 * File:   Background.h
 * Author: roberto
 *
 * Created on 6 agosto 2013, 13.10
 */

typedef enum {spa,sapa,srl,srls} society;

typedef struct {
    char* name;
    society type;
    float found;
    float x[50];
    float y[50];
} Company;

void init_company();
Company getCompany(int n);
char* type2Text(society val);