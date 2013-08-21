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
    float x[15];
    float y[15];
} Company;

void init_company();
Company getCompany(int n);
void update();

char* type2Text(society val);