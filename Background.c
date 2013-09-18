/**
 * Qui verranno istanziati le varie Company e il server di aggiornamenti dei Found
 */
#include "Background.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

Data_notebook *new_data_notebook(){
    Data_notebook *data;
    data=malloc(sizeof(Data_notebook));
    return data;
}

Company Company0,Company1,Company2,Company3,Company4,Company5;

void init_company(){
    {
        Company0.name = "Pincopallino industries";
        Company0.type = spa;
        int n;
        for(n=0;n<POINTS;n++){
            Company0.x[n]=n;
        }
        for(n=0;n<POINTS;n++){
            Company0.y[n]=random()%20;
        }
        Company0.found = Company0.y[POINTS-1];
        //Company0.found = 150000;
    }
    {
        Company1.name = "La fattoria di Giuseppina";
        Company1.type = sapa;
        int n;
        for(n=0;n<POINTS;n++){
            Company1.x[n]=n;
        }
        for(n=0;n<POINTS;n++){
            Company1.y[n]=random()%20;
        }
        Company1.found = Company1.y[POINTS-1];
        //Company1.found = 30000;
    }
    {
        Company2.name = "Abstergo";
        Company2.type = srl;
        int n;
        for(n=0;n<POINTS;n++){
            Company2.x[n]=n;
        }
        for(n=0;n<POINTS;n++){
            Company2.y[n]=random()%20;
        }
        Company2.found = Company2.y[POINTS-1];
        //Company2.found = 1700000;
    }
    {
        Company3.name = "Aperture";
        Company3.type = srls;
        int n;
        for(n=0;n<POINTS;n++){
            Company3.x[n]=n;
        }
        for(n=0;n<POINTS;n++){
            Company3.y[n]=random()%20;
        }
        Company3.found = Company3.y[POINTS-1];
        //Company3.found = 5000000;
    }
    {
        Company4.name = "I demolitori di vecchi\n e adorati ricordi";
        Company4.type = spa;
        int n;
        for(n=0;n<POINTS;n++){
            Company4.x[n]=n;
        }
        for(n=0;n<POINTS;n++){
            Company4.y[n]=random()%20;
        }
        Company4.found = Company4.y[POINTS-1];
        //Company4.found = 125000; 
    }
    {
        Company5.name = "Non siamo la NASA";
        Company5.type = spa;
        int n;
        for(n=0;n<POINTS;n++){
            Company5.x[n]=n;
        }
        for(n=0;n<POINTS;n++){
            Company5.y[n]=random()%20;
        }
        Company5.found = Company5.y[POINTS-1];
        //Company5.found = 10000;
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

Company* get_Company(int n){
    if (n==0)
       return &Company0;
    else if (n==1)
        return &Company1;
    else if (n==2)
        return &Company2;
    else if (n==3)
        return &Company3;
    else if (n==4)
        return &Company4;
    else if (n==5)
        return &Company5;
    else
        printf("Company selezionata non esistente\n");
}

bool update(){
    int n;
    for(n=0;n<POINTS;n++){
            Company0.y[n]=random()%20;
            Company1.y[n]=random()%20;
            Company2.y[n]=random()%20;
            Company3.y[n]=random()%20;
            Company4.y[n]=random()%20;
            Company5.y[n]=random()%20;
        }
    return true;
}

void Buy(GtkWidget *widget, gpointer data){

    GtkWidget *dialog, *label, *input, *bancomat;
    /* Create the widgets */
    dialog = gtk_dialog_new_with_buttons("Compra Azioni", data,
                                          GTK_DIALOG_DESTROY_WITH_PARENT,
                                          GTK_STOCK_OK);
    
    gtk_widget_set_usize(GTK_WIDGET(dialog),350,200);
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
    bancomat = gtk_image_new_from_file("images/bancomat.png");
    gtk_widget_set_usize(GTK_WIDGET(bancomat),100,100);
    label = gtk_label_new ("Inserire la quota di azioni che si vuole aquisire");
    input = gtk_entry_new();
    
    /* Ensure that the dialog box is destroyed when the user responds. */
    g_signal_connect_swapped (dialog,"response",
                              G_CALLBACK (gtk_widget_destroy), dialog);

    /* Add the label, and show everything we've added to the dialog. */
    gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox),
                       bancomat);
    gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox),
                       label);
    gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox),
                       input);

    gtk_widget_show_all (dialog);
}

void Sell(GtkWidget *widget, gpointer data){
    
    GtkWidget *dialog, *label, *input, *bancomat;
    /* Create the widgets */
    dialog = gtk_dialog_new_with_buttons("Vendi Azioni", data,
                                          GTK_DIALOG_DESTROY_WITH_PARENT,
                                          GTK_STOCK_OK);
    
    gtk_widget_set_usize(GTK_WIDGET(dialog),350,200);
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
    bancomat = gtk_image_new_from_file("images/bancomat.png");
    gtk_widget_set_usize(GTK_WIDGET(bancomat),100,100);
    label = gtk_label_new ("Inserire la quota di azioni che si e' disposti a vendere");
    input = gtk_entry_new();
    
    /* Ensure that the dialog box is destroyed when the user responds. */
    g_signal_connect_swapped (dialog,"response",
                              G_CALLBACK (gtk_widget_destroy), dialog);

    /* Add the label, and show everything we've added to the dialog. */
    gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox),
                       bancomat);
    gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox),
                       label);
    gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox),
                       input);

    gtk_widget_show_all (dialog);
    
}

char* found2Text(float found){
    char str[12];
    snprintf(str, sizeof(str), "%.03f", found);
    return &str;
}

/*
 * Le righe seguenti servono a convertire il type in una stringa
 * Creiamo una stuttura per le associazioni
 */ 
typedef struct{
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
    }

    return ("!!invalid type val!!");
}
    
