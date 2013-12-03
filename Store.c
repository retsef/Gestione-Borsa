#include "Store.h"
#include "Widget.h"

pthread_mutex_t lock;
char* strings;

static int ID = 1;
static Company *Company0, *Company1, *Company2, *Company3, *Company4, *Company5;
static Company_exposer *Company_exposer0, *Company_exposer1, *Company_exposer2, *Company_exposer3, *Company_exposer4, *Company_exposer5;
static Action *Action_company0, *Action_company1, *Action_company2, *Action_company3, *Action_company4, *Action_company5;
static User *Azionista;

Company* new_Company(){
    Company* cmp = (Company *) malloc(sizeof(Company));
    cmp->found = 0;
    cmp->point = 0;
    cmp->name = "";
    cmp->stats_found = 0;
    cmp->stats_point = 0;
    cmp->type = 0;
    cmp->max = 0;
    cmp->min = 0;
    cmp->pre_point = 0;
    cmp->point = 0;
    int i;
    for(i=0;i<POINTS;i++){
    cmp->x[i] = i;
    cmp->y[i] = 0;
    cmp->midvalue[i] = 0;
    }
    cmp->id = ID;
    cmp->idle=0;
    cmp->frame_content = new_Company_frame_content();
    cmp->action = NULL;
    return cmp;
}

void destroy_Company(Company* pCompany){
    if(pCompany!=NULL){
    pthread_kill(pCompany->thread, 0);
    destroy_Company_frame_content(pCompany->frame_content);
    free(pCompany);
    }
    pthread_mutex_destroy(&lock);
    return;
}
/*
void init_all_Company(GtkNotebook* notebook, GtkWidget* window){
    int n, cmp;
    {
        Company0 = new_Company();
        Company1 = new_Company();
        Company2 = new_Company();
        Company3 = new_Company();
        Company4 = new_Company();
        Company5 = new_Company();
    }
    
    Company0->name = "Pincopallino industries";
    Company0->type = spa;
    
    Company1->name = "La fattoria di Giuseppina";
    Company1->type = sapa;
    
    Company2->name = "Abstergo";
    Company2->type = srl;
    
    Company3->name = "Aperture";
    Company3->type = srls;
    
    Company4->name = "I demolitori di vecchi\n e adorati ricordi";
    Company4->type = spa;
    
    
    Company5->name = "Non siamo la NASA";
    Company5->type = sapa;
    
    for(cmp=0;cmp<6;cmp++){
        Company *Cmp_obj = get_Company(cmp);
        for(n=0;n<POINTS;n++){
            Cmp_obj->y[n]=Cmp_obj->y[n-1]+( pow(-1,random()%2)*(random()%10) );
            Cmp_obj->midvalue[n] = middle_value(Cmp_obj->y, POINTS);
        }
        //gtk_label_set_text(GTK_LABEL(Cmp_obj->action->content->name), Cmp_obj->name);
        //gtk_label_set_text(GTK_LABEL(Cmp_obj->action->content->type), type2text(Cmp_obj->type));
        Cmp_obj->found = Cmp_obj->y[POINTS-1];
        Cmp_obj->point = Cmp_obj->point+(pow(-1,random()%2) * ((random()%3)*(pow(10,(pow(-1,random()%2)*(random()%2))))));
        if(Cmp_obj->point<=0)
                Cmp_obj->point=0,01;
        Cmp_obj->max = max_value(Cmp_obj->y, POINTS);
        Cmp_obj->min = min_value(Cmp_obj->y, POINTS);
        Cmp_obj->stats_found = stats_float_value(Cmp_obj->y, POINTS);
        Cmp_obj->stats_point = stats_point_value(Cmp_obj->pre_point, Cmp_obj->point);
        
        //Cmp_obj->idle = pthread_create(&Cmp_obj->thread,NULL,update_graph_value,(void *) Cmp_obj);
    }
    
}*/

void INIT_ALL(GtkNotebook* notebook, GtkFixed* Container, GtkWidget* window){
    int n, cmp;
    {
        Company0 = new_Company();
        Company1 = new_Company();
        Company2 = new_Company();
        Company3 = new_Company();
        Company4 = new_Company();
        Company5 = new_Company();
    }
    {
        Company_exposer0 = new_Company_exposer();
        Company_exposer1 = new_Company_exposer();
        Company_exposer2 = new_Company_exposer();
        Company_exposer3 = new_Company_exposer();
        Company_exposer4 = new_Company_exposer();
        Company_exposer5 = new_Company_exposer();
    }
    
    Company0->name = "Pincopallino industries";
    Company0->type = spa;
    
    Company1->name = "La fattoria di Giuseppina";
    Company1->type = sapa;
    
    Company2->name = "Abstergo";
    Company2->type = srl;
    
    Company3->name = "Aperture";
    Company3->type = srls;
    
    Company4->name = "I demolitori di vecchi\n e adorati ricordi";
    Company4->type = spa;
    
    
    Company5->name = "Non siamo la NASA";
    Company5->type = sapa;
    
    {
        Action_company0 = new_Action(get_Company(0),get_User());
        Action_company1 = new_Action(get_Company(1),get_User());
        Action_company2 = new_Action(get_Company(2),get_User());
        Action_company3 = new_Action(get_Company(3),get_User());
        Action_company4 = new_Action(get_Company(4),get_User());
        Action_company5 = new_Action(get_Company(5),get_User());
    }
    
    for(cmp=0;cmp<6;cmp++){
        Company *Cmp_obj = get_Company(cmp);
        for(n=0;n<POINTS;n++){
            Cmp_obj->y[n]=Cmp_obj->y[n-1]+( pow(-1,random()%2)*(random()%10) );
            Cmp_obj->midvalue[n] = middle_value(Cmp_obj->y, POINTS);
        }
        //gtk_label_set_text(GTK_LABEL(Cmp_obj->action->content->name), Cmp_obj->name);
        //gtk_label_set_text(GTK_LABEL(Cmp_obj->action->content->type), type2text(Cmp_obj->type));
        Cmp_obj->found = Cmp_obj->y[POINTS-1];
        Cmp_obj->point = Cmp_obj->point+(pow(-1,random()%2) * ((random()%3)*(pow(10,(pow(-1,random()%2)*(random()%2))))));
        if(Cmp_obj->point<=0)
                Cmp_obj->point=0,01;
        Cmp_obj->max = max_value(Cmp_obj->y, POINTS);
        Cmp_obj->min = min_value(Cmp_obj->y, POINTS);
        Cmp_obj->stats_found = stats_float_value(Cmp_obj->y, POINTS);
        Cmp_obj->stats_point = stats_point_value(Cmp_obj->pre_point, Cmp_obj->point);
        
        //Cmp_obj->idle = pthread_create(&Cmp_obj->thread,NULL,update_graph_value,(void *) Cmp_obj);
    }
    {
        gtk_fixed_put(Container,get_Action(0)->content->frame, 10, 5);
        gtk_fixed_put(Container,get_Action(1)->content->frame, 10, 115);
        gtk_fixed_put(Container,get_Action(2)->content->frame, 10, 230);
        gtk_fixed_put(Container,get_Action(3)->content->frame, 340, 5);
        gtk_fixed_put(Container,get_Action(4)->content->frame, 340, 115);
        gtk_fixed_put(Container,get_Action(5)->content->frame, 340, 230);
    }
    
    for(n=0;n<6;n++){
        get_Company_exposer(n)->button = gtk_button_new_with_label(get_Company(n)->name);
        get_Company_exposer(n)->label = create_notebook_label(get_Company(n)->name, GTK_NOTEBOOK(notebook),TRUE, get_Company(n)->id);
        get_Company_exposer(n)->graph = create_graph_with_rules(get_Company(n)->x, get_Company(n)->y, get_Company(n)->midvalue, POINTS);
        get_Company_exposer(n)->frame = create_company_frame_graph(get_Company(n), get_Company_exposer(n)->graph, window);
        get_Company_exposer(n)->notebook = notebook;
        //evento
        g_signal_connect(G_OBJECT(get_Company_exposer(n)->button), "clicked", 
            (GtkSignalFunc)create_company_tab, get_Company_exposer(n));
        //gtk_notebook_append_page(GTK_NOTEBOOK(notebook), Company_exposer0->frame, Company_exposer0->label);
        
        get_Company(n)->idle = pthread_create(&get_Company(n)->thread,NULL,update_graph_value,(void *) get_Company(n));
    }
    return;
}

/* Mantiene aggiornati i valori realtivi le info statistiche delle Company */
void *update_graph_value(void *ptr){
    if(ptr!=NULL){
        Company* pCompany = (Company*) ptr;

        int n;
        while(true){
        gdk_threads_enter();
        pthread_mutex_lock(&lock);
        //printf("%s thread start\n", pCompany->name);
            for(n=0; n<POINTS; n++){
                pCompany->y[n]=pCompany->y[n+1];
                pCompany->midvalue[n] = middle_value(pCompany->y, POINTS);
            }
        pCompany->y[POINTS-1]=pCompany->y[POINTS-2]+( pow(-1,random()%2)*(random()%10) );
        pCompany->found = pCompany->y[POINTS-1];
        pCompany->pre_point = pCompany->point;
        pCompany->point = pCompany->point+(pow(-1,random()%2) * ((random()%3)*(pow(10,(pow(-1,random()%2)*(random()%2))))));
        if(pCompany->point<=0)
            pCompany->point=0,01;

        pCompany->max = max_value(pCompany->y, POINTS);
        pCompany->min = min_value(pCompany->y, POINTS);
        pCompany->stats_found = stats_float_value(pCompany->y, POINTS);
        pCompany->stats_point = stats_point_value(pCompany->pre_point, pCompany->point);
        
        if(pCompany->frame_content!=NULL){
            gtk_label_set_label(GTK_LABEL(pCompany->frame_content->found), float2text(pCompany->found));
            gtk_label_set_label(GTK_LABEL(pCompany->frame_content->point), float2text(pCompany->point));
            gtk_label_set_label(GTK_LABEL(pCompany->frame_content->midvalue), float2text(pCompany->midvalue[0]));
            gtk_label_set_label(GTK_LABEL(pCompany->frame_content->stats_found), float2text(pCompany->stats_found));
            gtk_label_set_label(GTK_LABEL(pCompany->frame_content->stats_point), float2text(pCompany->stats_point));
            gtk_label_set_label(GTK_LABEL(pCompany->frame_content->max), float2text(pCompany->max));
            gtk_label_set_label(GTK_LABEL(pCompany->frame_content->min), float2text(pCompany->min));
        }
        //printf("%s thread stop\n", pCompany->name);
        pthread_mutex_unlock(&lock);
        gdk_threads_leave();
        usleep(1000000);
        //usleep(400000);
        //nanosleep((struct timespec[]){{0, 70000000}}, NULL);

        //gtk_main_iteration();
        }
    }
    return;
}

Company* get_Company(int index){
    if(index==0){
        return Company0;
    }else if(index==1){
        return Company1;
    }else if(index==2){
        return Company2;
    }else if(index==3){
        return Company3;
    }else if(index==4){
        return Company4;
    }else if(index==5){
        return Company5;
    }else{
        printf("Company all'indice %d non trovata", &index);
        return NULL;
    }
}
Action* get_Action(int index){
    if(index==0){
        return Action_company0;
    } else if(index==1){
        return Action_company1;
    } else if(index==2){
        return Action_company2;
    } else if(index==3){
        return Action_company3;
    } else if(index==4){
        return Action_company4;
    } else if(index==5){
        return Action_company5;
    } else return NULL;
}
Action* get_Action_from_Company(Company* cmp){
    int i;
    for(i=0; i<6; i++){
        Company* company = get_Action(i)->company;
        if(cmp->name==company->name)
            return get_Action(i);
    }
    return NULL;
}
Company_exposer* get_Company_exposer(int index){
    if(index==0){
        return Company_exposer0;
    } else if(index==1){
        return Company_exposer1;
    } else if(index==2){
        return Company_exposer2;
    } else if(index==3){
        return Company_exposer3;
    } else if(index==4){
        return Company_exposer4;
    } else if(index==5){
        return Company_exposer5;
    } else return NULL;
}

User* new_User(Money bank){
    User* usr = (User *) malloc(sizeof(User));
    usr->wallet = bank;
    return usr;
}
User* get_User(){
    return Azionista;
}
void destroy_User(User* usr){
    if(usr!=NULL)
        free(usr);
    else
        printf("Impossibile liberare memoria occupata da un User");
    return;
}
void init_User(Money wallet){
    Azionista = new_User(wallet);
    return;
}

Action* new_Action(Company* pCompany, User* pActionist){
    Action* act = (Action *) malloc(sizeof(Action));
    act->actionist = pActionist;
    act->company = pCompany;
    act->content = new_Action_content(pCompany);
    act->dialog = new_Action_dialog();
    act->found = 0;
    act->stats = 0;
    act->pre_found = 0;
    return act;
}
/*
void create_Action(Action* act){
    
}*/
void destroy_Action(Action* act){
    if(act!=NULL)
        free(act);
    else
        printf("Impossibile distruggere una Action");
    return;
}


void Buy_action(Action* act){
    //printf("%s",value);
    //Action_dialog* act = pCompany->action->dialog;
    const char* str = "";
    str = gtk_entry_get_text(GTK_ENTRY(act->dialog->input));
    //printf("%s", str);
    if(Can_Pay(act, (char*)str)==true){
        //exit_Action(act);
        Pay(act,(char *) str);
        exit_Action(act->dialog);
    } else {
        gtk_label_set(GTK_LABEL(act->dialog->label), "Non puoi permetterti una mossa del genere!");
    }
    //printf("%s", str);
    return;
}

void Sell_action(Action* act){
    //printf("%s",value);
    //Action_dialog* act = pCompany->action->dialog;
    const char* str = 0;
    str = gtk_entry_get_text(GTK_ENTRY(act->dialog->input));
    
    //printf("%s", str);
    if(Can_Sell(act,(char*)str)==true){
        Sale(act,(char *) str);
        exit_Action(act->dialog);
    } else {
        gtk_label_set(GTK_LABEL(act->dialog->label), "Non puoi permetterti una mossa del genere!");
    }
    return;
}

bool Can_Pay(Action* act, char* str){
    if(is_a_float(str)==true){
        int intpart;
        intpart = act->actionist->wallet;
        printf("%d", intpart);
        if((intpart/char2float(str))>0)
            return true;
        else
            return false;
    } else {
        return false;
    }
}
bool Can_Sell(Action* act, char* str){
    if(is_a_float(str)==true){
        int intpart;
        intpart = act->found;
        if((intpart/char2float(str))>0)
            return true;
        else
            return false;
    } else {
        return false;
    }
}

void Pay(Action* act, char* str){
    float money = char2float(str);
    //printf("%f",money);
    int part = money/act->company->point;
    act->found = ((act->company->point)*(part));
    return;
}
void Sale(Action* act, char* str){
    float money = char2float(str);
    int part = money/act->company->point;
    act->actionist->wallet = part;
    return;
}

float middle_value(float arr[], int ln){
    if(ln<=0){
        printf("middle_value:La lunghezza dell'array non e' valida");
        return 0;
    }
    float vm = 0;
    int i;
    for(i=0;i<ln;i++){
        vm = vm + arr[i];
    }
    vm = vm/ln;
    return vm;
}

float stats_float_value(float arr[], int ln){
    if(ln<=0){
        printf("stats_value:La lunghezza dell'array non e' valida");
        return 0;
    }
    float st = 0;
    if(arr[ln-2]!=0)
        st = ((arr[ln-1]-arr[ln-2])/arr[ln-2])*100;
    
    return st;

}

float stats_point_value(float pre_point, float point){
    float st = 0;
    if(pre_point!=0)
        st = ((point-pre_point)/pre_point)*100;
    
    return st;
}

float stats_action(float pre_found, float found){
    float st = 0;
    if(pre_found!=0)
        st = ((found-pre_found)/pre_found)*100;
    
    return st;
}


float max_value(float arr[], int ln){
    if(ln<=0){
        printf("max_value:La lunghezza dell'array non e' valida");
        return 0;
    }
    float max = arr[0];
    int i;
    for(i=0;i<ln;i++){
        if(arr[i]>max)
            max = arr[i];
    }
    return max;
}

float min_value(float arr[], int ln){
    if(ln<=0){
        printf("min_value:La lunghezza dell'array non e' valida");
        return 0;
    }
    float min = arr[0];
    int i;
    for(i=0;i<ln;i++){
        if(arr[i]<min)
            min = arr[i];
    }
    return min;
}


bool is_a_float(char* str){
    if(str!=NULL){
    int i=0,com=0;
    if(str[i]==',')
        return false;
    //printf("%d",strlen(str));
    for(i=0;i<strlen(str);i++){
        if(str[i]=='0'||str[i]=='1'||str[i]=='2'||str[i]=='3'||
                str[i]=='4'||str[i]=='5'||str[i]=='6'||
                str[i]=='7'||str[i]=='8'||str[i]=='9'||str[i]==','){
            if(str[i]==',')
                com++;
        } else {
            return false;
        }
        
    }
    if(com>1)
        return false;
    else
        return true;
    }
    printf("is_a_float:Valore di input non valido");
    return false;
}

char* float2text(float value){
    if(strings==NULL)
        strings = (char *) malloc(sizeof(char*));
    //char* str = (char *) malloc(sizeof(char*));
    sprintf(strings, "%.02f", value);
    if(strings!=NULL)
        return strings;
    //return NULL;
    
    printf("float2text:Impossibile eseguire la conversione");
    return "";
}

float char2float(char* chr){
    if(chr!=NULL){
        float flt;
        flt = atof(chr);
        return flt;
    }
    printf("char2float:Valore di input non valido");
    return 0;
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
char* type2text(society val){
    int map_sz = sizeof(type_list) / sizeof(*type_list);
    int n;
     
    for (n=0; n < map_sz; n++)
    {
        if (type_list[n].val == val)
            return type_list[n].val_name;
    }

    return ("!!invalid type val!!");
}
