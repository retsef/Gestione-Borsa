/**
 * Qui verranno istanziati le varie Company e il server di aggiornamenti dei Found
 */
#include "Background.h"
#include <string.h>
/*
typedef char string[150];

typedef enum {spa,sapa,srl,srls} society;

typedef struct {
    string name;
    society type;
    float found;
    float x[30];
    float y[30];
} Company;
*/

static Company Company0,Company1,Company2,Company3,Company4,Company5;

void init_company(){
    {
        strcpy (Company0.name, "Pincopallino industries");
        Company0.type = spa;
        Company0.found = 150000;
    }
    {
        strcpy (Company1.name, "La fattoria di Giuseppina");
        Company1.type = sapa;
        Company1.found = 30000;
    }
    {
        strcpy (Company2.name, "Abstergo");
        Company2.type = srl;
        Company2.found = 1700000;
    }
    {
        strcpy (Company3.name, "Aperture");
        Company3.type = srls;
        Company3.found = 5000000;
    }
    {
       strcpy (Company4.name, "I demolitori di vecchi\n e adorati ricordi");
        Company4.type = spa;
        Company4.found = 125000; 
    }
    {
        strcpy (Company5.name, "Non siamo la NASA");
        Company5.type = spa;
        Company5.found = 10000;
    }
}

Company getCompany(int n){
    if (n=0)
       return Company0;
    else if (n=1)
        return Company1;
    else if (n=2)
        return Company2;
    else if (n=3)
        return Company3;
    else if (n=4)
        return Company4;
    else if (n=5)
        return Company5;
    else
        g_print("Company selezionata non esistente");
}
    
