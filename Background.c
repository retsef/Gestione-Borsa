/**
 * Qui verranno istanziati le varie Company e il server di aggiornamenti dei Found
 */
#include "Background.h"
#include <string.h>

static Company Company0,Company1,Company2,Company3,Company4,Company5;

void init_company(){
    {
        Company0.name = "Pincopallino industries";
        Company0.type = spa;
        int n;
        for(n=0;n<=15;n++){
            Company0.x[n]=n;
            Company0.y[n]=1;
        }
        Company0.found = 150000;
    }
    {
        Company1.name = "La fattoria di Giuseppina";
        Company1.type = sapa;
        Company1.found = 30000;
    }
    {
        Company2.name = "Abstergo";
        Company2.type = srl;
        Company2.found = 1700000;
    }
    {
        Company3.name = "Aperture";
        Company3.type = srls;
        Company3.found = 5000000;
    }
    {
        Company4.name = "I demolitori di vecchi\n e adorati ricordi";
        Company4.type = spa;
        Company4.found = 125000; 
    }
    {
        Company5.name = "Non siamo la NASA";
        Company5.type = spa;
        Company5.found = 10000;
    }
}

Company get_Company_by_name(const char* name){
    if(strcmp(name,Company0.name)==0)
        return Company0;
    else if(strcmp(name,Company1.name)==0)
        return Company1;
    else if(strcmp(name,Company2.name)==0)
        return Company2;
    else if(strcmp(name,Company3.name)==0)
        return Company3;
    else if(strcmp(name,Company4.name)==0)
        return Company4;
    else if(strcmp(name,Company5.name)==0)
        return Company5;
    else
        printf("\nNon esiste una Company con quel nome\n");
}

Company get_Company(int n){
    if (n==0)
       return Company0;
    else if (n==1)
        return Company1;
    else if (n==2)
        return Company2;
    else if (n==3)
        return Company3;
    else if (n==4)
        return Company4;
    else if (n==5)
        return Company5;
    else
        printf("Company selezionata non esistente\n");
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
    
