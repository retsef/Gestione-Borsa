/* 
 * File:   Background.h
 * Author: roberto
 *
 * Created on 6 agosto 2013, 13.10
 */

typedef char string[150];

typedef enum {spa,sapa,srl,srls} society;

typedef struct {
    string name;
    society type;
    float found;
    float x[30];
    float y[30];
} Company;

void init_company();
Company getCompany(int n);
