#include "Widget.h"

//static Company_exposer *Company_exposer0, *Company_exposer1, *Company_exposer2, *Company_exposer3, *Company_exposer4, *Company_exposer5;
//static Action *Action_company0, *Action_company1, *Action_company2, *Action_company3, *Action_company4, *Action_company5;

Company_exposer* new_Company_exposer(){
    Company_exposer* cmp_exp = (Company_exposer *) malloc(sizeof(Company_exposer));
    cmp_exp->button = NULL;
    cmp_exp->frame = NULL;
    cmp_exp->graph = NULL;
    cmp_exp->label = NULL;
    cmp_exp->notebook = NULL;
    return cmp_exp;
}

void destroy_Company_exposer(Company_exposer* cmp_exp){
    if(cmp_exp!=NULL)
        free(cmp_exp);
    return;
}


Company_frame_content* new_Company_frame_content(){
    Company_frame_content* cmp_frm = (Company_frame_content *) malloc(sizeof(Company_frame_content));
    cmp_frm->container = NULL;
    cmp_frm->template = NULL;
    cmp_frm->found = NULL;
    cmp_frm->point = NULL;
    cmp_frm->midvalue = NULL;
    cmp_frm->max = NULL;
    cmp_frm->min = NULL;
    cmp_frm->name = NULL;
    cmp_frm->stats_found = NULL;
    cmp_frm->stats_point = NULL;
    cmp_frm->type = NULL;
    return cmp_frm;
}

void destroy_Company_frame_content(Company_frame_content* cmp_frm){
    if(cmp_frm!=NULL)
        free(cmp_frm);
    return;
}


Action_dialog* new_Action_dialog(){
    Action_dialog* act = (Action_dialog *) malloc(sizeof(Action_dialog));
    act->label = gtk_label_new ("Quanto vorresti investire?");
    act->bancomat = gtk_image_new_from_file("images/bancomat.png");
    
    act->hbox = gtk_hbox_new(FALSE, 2);
    act->ok = gtk_button_new_from_stock(GTK_STOCK_OK);
    act->cancel = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
    act->dialog = gtk_dialog_new();
    
    act->input = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(act->input), "Inserisci l'importo");
    
    gtk_widget_set_usize(GTK_WIDGET(act->dialog),350,200);
    
    gtk_window_set_resizable(GTK_WINDOW(act->dialog), FALSE);
    gtk_widget_set_usize(GTK_WIDGET(act->bancomat),100,100);

    gtk_box_pack_start(GTK_BOX(act->hbox), act->ok, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(act->hbox), act->cancel, TRUE, TRUE, 0);
    
    /* Add the widget, and show everything we've added to the dialog. */
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(act->dialog)->vbox), act->bancomat);
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(act->dialog)->vbox), act->label);
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(act->dialog)->vbox), act->input);
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(act->dialog)->vbox), act->hbox);
    
    return act;
}

void destroy_Action_dialog(Action_dialog* act){
    if(act!=NULL)
        free(act);
    return;
}


Action_content* new_Action_content(Company* pCompany){
    Action_content* act_cnt = (Action_content *) malloc(sizeof(Action_content));
    
    act_cnt->frame = gtk_frame_new("Company");
    act_cnt->container = gtk_fixed_new();
    
    act_cnt->template = gtk_label_new("Nome:                                               tipo:\n\n"
            "Fondi:                           $   stato:                 %\n"
            "Fondi Inv.:                     $   stato:                 %");
    
    act_cnt->name = gtk_label_new(pCompany->name);
    act_cnt->type = gtk_label_new(type2text(pCompany->type));
    
    act_cnt->found = gtk_label_new(float2text(pCompany->found));
    act_cnt->stats = gtk_label_new(float2text(pCompany->stats_found));
    
    act_cnt->own_action = gtk_label_new("Null");
    act_cnt->own_stats = gtk_label_new("Null");
    
    gtk_container_add(GTK_CONTAINER(act_cnt->frame), act_cnt->container);
    
    gtk_fixed_put(GTK_FIXED(act_cnt->container),act_cnt->template, 5, 0);
    gtk_fixed_put(GTK_FIXED(act_cnt->container),act_cnt->name, 60, 0);
    gtk_fixed_put(GTK_FIXED(act_cnt->container),act_cnt->type, 280, 00);
    gtk_fixed_put(GTK_FIXED(act_cnt->container),act_cnt->found, 90, 40);
    gtk_fixed_put(GTK_FIXED(act_cnt->container),act_cnt->stats, 235, 40);
    gtk_fixed_put(GTK_FIXED(act_cnt->container),act_cnt->own_action, 90, 65);
    gtk_fixed_put(GTK_FIXED(act_cnt->container),act_cnt->own_stats, 235, 65);
    
    gtk_widget_set_size_request(act_cnt->frame,320,110);
    
    return act_cnt;
}

void destroy_Action_content(Action_content* act_cnt){
    if(act_cnt!=NULL)
        free(act_cnt);
    return;
}

Actionist_Profile* new_Actionist_profile(User* pActionist, GtkFixed* Container){
    Actionist_Profile* act_prf = (Actionist_Profile *) malloc(sizeof(Actionist_Profile));
    act_prf->frame_home = gtk_frame_new("Info Finanziarie");
    act_prf->home_container = gtk_fixed_new();
    
    act_prf->template = gtk_label_new("Fondi:");
    act_prf->home_found = gtk_label_new(float2text(pActionist->wallet));
    gtk_fixed_put(GTK_FIXED(act_prf->home_container), act_prf->home_found, 70, 5);
    gtk_container_add(GTK_CONTAINER(act_prf->frame_home), act_prf->home_container);
    
    gtk_fixed_put(GTK_FIXED(act_prf->home_container),act_prf->template, 5, 5);
    
    act_prf->frame_action = gtk_frame_new("Info Azioni coninvolte");
    act_prf->action_container = gtk_fixed_new();

    gtk_container_add(GTK_CONTAINER(act_prf->frame_action), act_prf->action_container);
            
    gtk_widget_set_size_request(act_prf->frame_home,220,60);
    gtk_widget_set_size_request(act_prf->frame_action,685,385);
    
    gtk_fixed_put(Container,act_prf->frame_home,400,0);
    gtk_fixed_put(Container,act_prf->frame_action,5,60);
    
    //act_prf->thread = 
    
    return act_prf;
}

void destroy_Actionist_profile(Actionist_Profile* act_prf){
    if(act_prf!=NULL)
        pthread_kill(act_prf->thread,0);
        free(act_prf);
    return;
}


/*
void init_all_Action(GtkFixed* Container){
    {
        Action_company0 = new_Action(get_Company(0),get_User());
        Action_company1 = new_Action(get_Company(1),get_User());
        Action_company2 = new_Action(get_Company(2),get_User());
        Action_company3 = new_Action(get_Company(3),get_User());
        Action_company4 = new_Action(get_Company(4),get_User());
        Action_company5 = new_Action(get_Company(5),get_User());
    }
    {
        gtk_fixed_put(Container,get_Action(0)->content->frame, 10, 5);
        gtk_fixed_put(Container,get_Action(1)->content->frame, 10, 115);
        gtk_fixed_put(Container,get_Action(2)->content->frame, 10, 230);
        gtk_fixed_put(Container,get_Action(3)->content->frame, 340, 5);
        gtk_fixed_put(Container,get_Action(4)->content->frame, 340, 115);
        gtk_fixed_put(Container,get_Action(5)->content->frame, 340, 230);
    }
    return;
}*/
/*
void init_all_Company_exposer(GtkNotebook* notebook, GtkWidget* window){
    int n;
    {
        Company_exposer0 = new_Company_exposer();
        Company_exposer1 = new_Company_exposer();
        Company_exposer2 = new_Company_exposer();
        Company_exposer3 = new_Company_exposer();
        Company_exposer4 = new_Company_exposer();
        Company_exposer5 = new_Company_exposer();
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
}*/

/*Crea la finestra di About */
void show_about(GtkWidget *widget, gpointer data){
    GdkPixbuf *image = gdk_pixbuf_new_from_file("images/money.png", NULL);
    GtkWidget *dialog = gtk_about_dialog_new();
    const char *author[] = { "Roberto Scinocca: \nroberto.scinocca@gmail.com \nhttp://www.github.com/retsef", NULL };
    
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),"Roberto Scinocca");
    gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog),"Gestione Borsa");
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog),"Simula i meccanismi degli azionisti");
    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), image);
    gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(dialog),
            "Gestione Borsa è software libero; è lecito redistribuirlo o modificarlo\n"
            "secondo i termini della GNU General Public License \n"
            "come pubblicata dalla Free Software Foundation;\n"
            "o la versione 2 o (a propria scelta) una versione successiva.\n\n"
            "Si veda la licenza GNU General Public License per maggiori dettagli.\n"
            "\nSi ringrazia la GNOME Foundation per le bellissime librerie GTK :D,"
            "\nil team del widget gtkdatabox per il plot in realtime,"
            "\ne non ultimo lo standard POSIX per i thread.");
    gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(dialog),author);
    g_object_unref(image), image = NULL;
    gtk_dialog_run(GTK_DIALOG (dialog));
    gtk_widget_destroy(dialog);
}

/**
 * Crea un pixbuf(buffer di pixel) per processare immagini
 * @param filename file immagine
 * @return un nuovo pixbuf
 */
GdkPixbuf *create_pixbuf(const gchar *filename){
    static GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    if(!pixbuf) {
       fprintf(stderr, "%s\n", error->message);
       g_error_free(error);
    }

    return pixbuf;
}

/**
 * Crea un tab per il notebook avente il bottone di chiusura
 * @param text Testo sulla linghuetta della tab
 * @param notebook Notebook a cui affiliare la tab
 * @param cloosable Se si vuole rendere la tab chiudibile
 * @param page Indice di tab
 * @return GtkWidget per il notebook
 */
GtkWidget *create_notebook_label(const char *text, GtkNotebook *notebook, bool cloosable, int page){
    GtkWidget *hbox; //Contenitore con disposizione orizzontale
    GtkWidget *label; //Label di intestanzione
    GtkWidget *button; //Bottone di chiusura
    GtkWidget *image; //Immagine del bottone
    
    hbox = gtk_hbox_new(FALSE, 3); 
    label = gtk_label_new(text);
        
    gtk_box_pack_start(GTK_BOX(hbox), label, TRUE, TRUE, 0);

    if(cloosable){
        button = gtk_button_new();
        image = gtk_image_new_from_stock(GTK_STOCK_CLOSE, GTK_ICON_SIZE_MENU);
        
        g_object_set_data(G_OBJECT(button), "page", GINT_TO_POINTER(page));
        /*Evento bottone*/
        g_signal_connect(G_OBJECT(button), "clicked",
                         G_CALLBACK(cb_close_tab),
                         GTK_NOTEBOOK(notebook));
        
        gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
        gtk_container_add(GTK_CONTAINER(button), image);
        gtk_button_set_relief(GTK_BUTTON(button), GTK_RELIEF_NONE);
    }

    gtk_widget_show_all(hbox);

    return(hbox);
}
/**
 * Funzione che interviene alla chiusura della tab
 * @param button Bottone "x" sulla tab
 * @param notebook Notebook a cui la tab e' ancorata
 */
static void cb_close_tab(GtkButton *button, GtkNotebook *notebook ){
    int page = 0;
    page = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "page"));
    
    //pthread_cancel();
    gtk_notebook_remove_page(notebook, page);
    return;
}
/**
 * Crea un Grafico (GtkDataBox) e lo attacca ad un Container
 * @param x Array di numeri per la X
 * @param y Array di numeri per la Y
 * @param graph_lenght Lunghezza del grafico
 * @return Un GtkWidget contenente il grafico
 */
GtkWidget * create_graph_with_rules(gfloat *x, gfloat *y, gfloat *mid, int graph_lenght){    
    GtkWidget *databox;
    GtkWidget *databoxcontainer;
    GtkDataboxGraph *graph;
    GtkDataboxGraph *midgraph;
    
    //gtk_box_pack_start(GTK_BOX(container), databoxcontainer, 1, 1, 0 );
    
    gtk_databox_create_box_with_scrollbars_and_rulers(
        &databox, &databoxcontainer, 
            FALSE, FALSE, TRUE, TRUE);

    GdkColor ActionColor = { 0, 65000, 0, 0 };
    GdkColor MidValueColor = { 0, 0, 65000, 0 };
    //errore qui poiche' non vi e' un passaggio di riferimento tra tipi ma tra puntatori
    graph = gtk_databox_lines_new(graph_lenght, x, y, &ActionColor, 1);
    midgraph = gtk_databox_lines_new(graph_lenght, x, mid, &MidValueColor, 1);
    gtk_databox_graph_add(GTK_DATABOX(databox), graph);
    gtk_databox_graph_add(GTK_DATABOX(databox), midgraph);
    
    //gtk_databox_set_total_limits(GTK_DATABOX(databox),0,POINTS, YMAX, YMIN);
    //gtk_databox_auto_rescale(GTK_DATABOX(databox), 0.005);
    g_idle_add_full(G_PRIORITY_DEFAULT_IDLE, (GSourceFunc) update_graph_scale, (gpointer) databox, NULL);
    
    gtk_widget_show_all(databoxcontainer);

    return(databoxcontainer);
}

GtkWidget * create_company_frame_graph(Company* Company_n, GtkWidget *Company_graph, gpointer window){
    GtkWidget *Company_frame = gtk_frame_new("Company");
    Company_n->frame_content->container = gtk_fixed_new();
    {
/*
        GtkWidget *Company_frame_info = gtk_frame_new("Info");
        gtk_frame_set_shadow_type(GTK_FRAME(Company_frame_info), GTK_SHADOW_IN);
        
        GtkWidget *Company_info_container = gtk_fixed_new();
*/
        Company_n->frame_content->template = gtk_label_new("Nome:                                                       Tipo:\n\n"
                                                   "Capitale:                     $                     $(P)                Max:\n"
                                                      "Stato:                     %                     %                         Min:");
        Company_n->frame_content->name = gtk_label_new(Company_n->name);
        Company_n->frame_content->type = gtk_label_new(type2text(Company_n->type));
        Company_n->frame_content->point = gtk_label_new(float2text(Company_n->point));
        Company_n->frame_content->found = gtk_label_new(float2text(Company_n->found));
        Company_n->frame_content->midvalue = gtk_label_new(float2text(Company_n->midvalue[0]));
        Company_n->frame_content->max = gtk_label_new(float2text(Company_n->max));
        Company_n->frame_content->min = gtk_label_new(float2text(Company_n->min));
        Company_n->frame_content->stats_found = gtk_label_new(float2text(Company_n->stats_found));
        Company_n->frame_content->stats_point = gtk_label_new(float2text(Company_n->stats_point));
        
        gtk_fixed_put(GTK_FIXED(Company_n->frame_content->container),Company_n->frame_content->template,10,10);
        gtk_fixed_put(GTK_FIXED(Company_n->frame_content->container),Company_n->frame_content->name,65,10);
        gtk_fixed_put(GTK_FIXED(Company_n->frame_content->container),Company_n->frame_content->type,315,10);
        gtk_fixed_put(GTK_FIXED(Company_n->frame_content->container),Company_n->frame_content->found,90,52);
        gtk_fixed_put(GTK_FIXED(Company_n->frame_content->container),Company_n->frame_content->point,190,52);
        gtk_fixed_put(GTK_FIXED(Company_n->frame_content->container),Company_n->frame_content->max,380,52);
        gtk_fixed_put(GTK_FIXED(Company_n->frame_content->container),Company_n->frame_content->min,380,71);
        gtk_fixed_put(GTK_FIXED(Company_n->frame_content->container),Company_n->frame_content->stats_found,90,71);
        gtk_fixed_put(GTK_FIXED(Company_n->frame_content->container),Company_n->frame_content->stats_point,190,71);
        
/*
        gtk_container_add(GTK_CONTAINER(Company_frame_info),Company_container);
        gtk_widget_set_size_request(Company_frame_info,350,80);
        gtk_fixed_put(GTK_FIXED(Company_container),Company_frame_info,2,2);
*/
        
        GtkWidget *Buy_button = gtk_button_new_with_label("Compra Azioni");
        GtkWidget *Sell_button = gtk_button_new_with_label("Vendi Azioni");

        gtk_widget_set_usize(GTK_WIDGET(Buy_button),180,40);
        gtk_widget_set_usize(GTK_WIDGET(Sell_button),180,40);
        
        Action* act = get_Action_from_Company(Company_n);
        Company_n->action = act;
        
        g_signal_connect(G_OBJECT(Buy_button), "clicked", 
                        G_CALLBACK(Buy), Company_n->action);
        g_signal_connect(G_OBJECT(Sell_button), "clicked", 
                        G_CALLBACK(Sell), Company_n->action);

        gtk_fixed_put(GTK_FIXED(Company_n->frame_content->container),Buy_button, 480,5);
        gtk_fixed_put(GTK_FIXED(Company_n->frame_content->container),Sell_button, 480,45);
    }   
    
    gtk_fixed_put(GTK_FIXED(Company_n->frame_content->container),Company_graph,5,105);
    gtk_widget_set_size_request(Company_graph,685,330);

    gtk_container_add(GTK_CONTAINER(Company_frame), Company_n->frame_content->container);
    
    return Company_frame;
}

void create_company_tab(GtkButton *button, Company_exposer *cmp_exp){
    
    gtk_notebook_insert_page(cmp_exp->notebook, cmp_exp->frame, cmp_exp->label, 1);
    gtk_widget_show_all(GTK_WIDGET(cmp_exp->notebook));
    
    gtk_notebook_set_current_page(cmp_exp->notebook, 1);
}

void Buy(GtkButton *button, Action* act){
    Action_dialog* buy = act->dialog;
    
    gtk_window_set_title(GTK_WINDOW(buy->dialog), "Compra Azioni");
    
    gtk_signal_connect_object(GTK_OBJECT(buy->ok), "clicked",
                              G_CALLBACK(Buy_action), act);
    
    gtk_signal_connect_object(GTK_OBJECT (buy->cancel), "clicked",
                               (GtkSignalFunc) exit_Action, act->dialog);

    gtk_widget_show_all(buy->dialog);
}

void Sell(GtkButton *button, Action* act){
    Action_dialog* sell = act->dialog;
    
    gtk_window_set_title(GTK_WINDOW(sell->dialog), "Compra Azioni");
    
    gtk_signal_connect_object(GTK_OBJECT(sell->ok), "clicked",
                              G_CALLBACK(Sell_action), act);
    
    gtk_signal_connect_object(GTK_OBJECT (sell->cancel), "clicked",
                               (GtkSignalFunc) exit_Action, act->dialog);

    gtk_widget_show_all(sell->dialog);
}

/* exit the application. */
void exit_Action(Action_dialog* act){
    gtk_widget_hide(act->dialog);
    //destroy_Action_dialog(act);
    return;
}

void *update_actionist_profile_draw(void *act){
    Actionist_Profile* act_prf = (Actionist_Profile*) act;
    int ind;
    while(true){
        gdk_threads_enter();
        pthread_mutex_lock(&lock);
        if(act_prf!=NULL){
            gtk_label_set_text(GTK_LABEL(act_prf->home_found),float2text(get_User()->wallet));

            for(ind=0; ind<6; ind++){
                gtk_label_set_text(GTK_LABEL(get_Action(ind)->content->found),float2text(get_Company(ind)->found));
                gtk_label_set_text(GTK_LABEL(get_Action(ind)->content->stats),float2text(get_Company(ind)->stats_found));

                Company* cmp = get_Action(ind)->company;
                //get_Action(i)->found = 0;
                if(cmp->y[POINTS-2]!=cmp->y[POINTS-1]){
                    get_Action(ind)->pre_found = get_Action(ind)->found;
                    float flt = get_Action(ind)->found*(cmp->stats_found);
                    //printf("%f\n",flt);
                    get_Action(ind)->found = get_Action(ind)->found + (flt);
                    if(get_Action(ind)->found>1){
                       //float flt_wall = get_Action(ind)->actionist->wallet ;
                       get_Action(ind)->actionist->wallet = get_Action(ind)->actionist->wallet + flt;
                    }
                }
                gtk_label_set_text(GTK_LABEL(get_Action(ind)->content->own_action),float2text(get_Action(ind)->found));

                get_Action(ind)->stats = stats_action(get_Action(ind)->pre_found, get_Action(ind)->found);
                gtk_label_set_text(GTK_LABEL(get_Action(ind)->content->own_stats),float2text(get_Action(ind)->stats));
            }

        }
        pthread_mutex_unlock(&lock);
        gdk_threads_leave();
        usleep(1000000);
    }
    
    return;
}
/* Funzione che forza il repaint del box */
bool update_graph_draw(GtkWidget* box){
    gtk_widget_queue_draw(GTK_WIDGET(box));
    return true;
}
/* Funzione che forza il rescale del plot(databox) */
bool update_graph_scale(GtkWidget* databox){
    gtk_databox_auto_rescale(GTK_DATABOX(databox), 0.005);
    return true;
}
/* Funzione di chiusura applicazione */
void exit_Application(){
    int i;
    for(i=0; i<6; i++){
    destroy_Company(get_Company(i));
    destroy_Company_exposer(get_Company_exposer(i));
    }
    pthread_mutex_destroy(&lock);
    gtk_main_quit();
}