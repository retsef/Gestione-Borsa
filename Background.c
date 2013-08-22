/**
 * Qui verranno istanziati le varie Company e il server di aggiornamenti dei Found
 */
#include "Background.h"
#include <stdlib.h>
#include <string.h>

typedef enum {spa,sapa,srl,srls} society;
/*
typedef struct {
    char* name;
    society type;
    float found;
    float x[15];
    float y[15];
} Company;*/
//per migliore astrazione con la struct Company creeremo dei puntatori ad esso come riferimenti
//quindi creiamo il Vero struct del company
struct _Company {
    char* name;
    society type;
    float found;
    float x[15];
    float y[15];
};
//Come per le gtk questo istanzia la struttura (in memoria) per l'oggetto che la richiama e azzera i suoi elementi
//quindi si dovra accedere agli elementi della struttura tramite puntatore
Company *Company_new() {
    Company *company = malloc(sizeof(Company));
    company->name = 0;
    company->found = 0;
    return company;
}

static Company *Company0,*Company1,*Company2,*Company3,*Company4,*Company5;

void init_company(){
    {
        Company0 = Company_new();
        Company0->name = "Pincopallino industries";
        Company0->type = spa;
        int n=0;
        for(n=0;n<15;n++){
            Company0->x[n]=n;
            Company0->y[n]=0;
        }
        Company0->found = 150000;
    }
    {
        Company1 = Company_new();
        Company1->name = "La fattoria di Giuseppina";
        Company1->type = sapa;
        Company1->found = 30000;
    }
    {
        Company2 = Company_new();
        Company2->name = "Abstergo";
        Company2->type = srl;
        Company2->found = 1700000;
    }
    {
        Company3 = Company_new();
        Company3->name = "Aperture";
        Company3->type = srls;
        Company3->found = 5000000;
    }
    {
        Company4 = Company_new();
        Company4->name = "I demolitori di vecchi\n e adorati ricordi";
        Company4->type = spa;
        Company4->found = 125000; 
    }
    {
        Company5 = Company_new();
        Company5->name = "Non siamo la NASA";
        Company5->type = spa;
        Company5->found = 10000;
    }
}

Company * getCompany(int n){
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

void update(){}

/*
 * Le righe seguenti servono a convertire il type in una stringa
 * Creiamo una stuttura per le associazioni
 */ 
typedef struct
{
    society val;
    char *val_name;
} type_TxtMap;
//Creiamo le associazioni
static const type_TxtMap type_list[] =
{
    {spa,"spa"},
    {sapa,"sapa"},
    {srl,"srl"},
    {srls,"srls"},
};
//trasformiamo il type in stringa
char* type2Text(society val){
    int map_sz = sizeof(type_list) / sizeof(*type_list);
    int n;
     
    for (n=0; n < map_sz; n++)
    {
        if (type_list[n].val == val)
            return type_list[n].val_name;
    }//for
 
    return ("!!invalid type val!!");
}
    
