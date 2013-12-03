/**
 * Qui verranno istanziati le varie Company e il server di aggiornamenti dei Found
 */
#include "Store.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <gtkdatabox.h>

static User Azionista;
static Company Company0,Company1,Company2,Company3,Company4,Company5;

void init_company(){
    {
        Company0.name = "Pincopallino industries";
        Company0.type = spa;
        int n;
        for(n=0;n<POINTS;n++){
            Company0.x[n]=n;
        }
        for(n=0;n<POINTS;n++){
            Company0.y[n]=Company0.y[n-1]+( pow(-1,random()%2)*(random()%10) );
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
            Company1.y[n]=Company1.y[n-1]+( pow(-1,random()%2)*(random()%10) );
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
            Company2.y[n]=Company2.y[n-1]+( pow(-1,random()%2)*(random()%10) );
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
            Company3.y[n]=Company3.y[n-1]+( pow(-1,random()%2)*(random()%10) );
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
            Company4.y[n]=Company4.y[n-1]+( pow(-1,random()%2)*(random()%10) );
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
            Company5.y[n]=Company5.y[n-1]+( pow(-1,random()%2)*(random()%10) );
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

Company* get_Company_by_found(const char* found){
    if(const_text2float(found)==get_Company(0)->found){
        return get_Company(0);
    } else if(const_text2float(found)==get_Company(1)->found){
        return get_Company(1);
    } else if(const_text2float(found)==get_Company(2)->found){
        return get_Company(2);
    } else if(const_text2float(found)==get_Company(3)->found){
        return get_Company(3);
    } else if(const_text2float(found)==get_Company(4)->found){
        return get_Company(4);
    } else if(const_text2float(found)==get_Company(5)->found){
        return get_Company(5);
    } else {}
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

bool update_graph (GtkWidget *box){
    int n;
    for(n=0;n<POINTS-1;n++){
        get_Company(0)->y[n]=get_Company(0)->y[n+1];
        get_Company(1)->y[n]=get_Company(1)->y[n+1];
        get_Company(2)->y[n]=get_Company(2)->y[n+1];
        get_Company(3)->y[n]=get_Company(3)->y[n+1];
        get_Company(4)->y[n]=get_Company(4)->y[n+1];
        get_Company(5)->y[n]=get_Company(5)->y[n+1];
    }
    get_Company(0)->y[POINTS-1]=get_Company(0)->y[POINTS-2]+( pow(-1,random()%2)*(random()%10) );
    get_Company(1)->y[POINTS-1]=get_Company(1)->y[POINTS-2]+( pow(-1,random()%2)*(random()%10) );
    get_Company(2)->y[POINTS-1]=get_Company(2)->y[POINTS-2]+( pow(-1,random()%2)*(random()%10) );
    get_Company(3)->y[POINTS-1]=get_Company(3)->y[POINTS-2]+( pow(-1,random()%2)*(random()%10) );
    get_Company(4)->y[POINTS-1]=get_Company(4)->y[POINTS-2]+( pow(-1,random()%2)*(random()%10) );
    get_Company(5)->y[POINTS-1]=get_Company(5)->y[POINTS-2]+( pow(-1,random()%2)*(random()%10) );
    
    get_Company(0)->found = get_Company(0)->y[POINTS-1];
    get_Company(1)->found = get_Company(1)->y[POINTS-1];
    get_Company(2)->found = get_Company(2)->y[POINTS-1];
    get_Company(3)->found = get_Company(3)->y[POINTS-1];
    get_Company(4)->found = get_Company(4)->y[POINTS-1];
    get_Company(5)->found = get_Company(5)->y[POINTS-1];
    
    gtk_widget_queue_draw(GTK_WIDGET(box));
    //gtk_notebook_set_current_page(GTK_NOTEBOOK(box),1);
    return true;
}

bool update_Company_info_found(GtkWidget *widget){
    char* str = float2Text(get_Company_by_found(gtk_label_get_text(GTK_LABEL(widget)))->found); 
    //printf(get_Company_by_found(gtk_label_get_text(GTK_LABEL(widget)))->name);
    //printf(str);
    //printf("\n");
    gtk_label_set_text(GTK_LABEL(widget), str);
    //gtk_widget_queue_draw(GTK_WIDGET(widget));
    return true;
}

bool update_graph_scale(GtkWidget *widget){
    gtk_databox_auto_rescale(GTK_DATABOX(widget), 0.005);
    return true;
}

bool update_Company_info_midvalue(GtkWidget *widget){
    //char* str = float2Text(get_Company_by_midvalue(strdup(gtk_label_get_text(GTK_LABEL(widget))))->found); 
    //printf(str);
    //printf("\n");
    //gtk_label_set_text(GTK_LABEL(widget), str);
    //gtk_widget_queue_draw(GTK_WIDGET(widget));
    return true;
}

bool update_Company_info_stats(GtkWidget *widget){
    
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
    char* money = strdup(gtk_entry_get_text(GTK_ENTRY(input)));
    
    /* Ensure that the dialog box is destroyed when the user responds. */
    g_signal_connect_swapped(dialog, "response",
                              G_CALLBACK(Buy_action), money);

    /* Add the widget, and show everything we've added to the dialog. */
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox),
                       bancomat);
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox),
                       label);
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox),
                       input);

    gtk_widget_show_all(dialog);
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
    
    char* money = strdup(gtk_entry_get_text(GTK_ENTRY(input)));
    
    /* Ensure that the dialog box is destroyed when the user responds. */
    g_signal_connect_swapped (dialog, "response",
                              G_CALLBACK(Sell_action), money);

    /* Add the label, and show everything we've added to the dialog. */
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox),
                       bancomat);
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox),
                       label);
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox),
                       input);
    
    gtk_widget_show_all(dialog);
    
}

void Buy_action(char* value){
    
}

void Sell_action(char* value){
    
}

char* float2Text(float value){
    char str[12];
    snprintf(str, sizeof(str), "%.03f", value);
    return &str;
    //char* hello = "123";
    //return hello;
}

float text2float(char* txt){
    return (float)atof(txt);
}

float const_text2float(const char* txt){
    return (float)atof(txt);
}

float Value_midrange(Company* pCompany){
    float aux;
    int i;
    for(i=0; i<POINTS; i++){
        aux = pCompany->y[i];
    }
    return (aux/POINTS);
}

float Statistics(Company* pCompany){
    float x = ((100*(pCompany->y[POINTS-1]-pCompany->y[POINTS-2]))/pCompany->y[POINTS-2]);
    return x;
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
    
