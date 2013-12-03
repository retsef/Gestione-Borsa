/* 
 * File:   main.c
 * Author: roberto
 *
 * Created on 4 ottobre 2013, 13.35
 */

#include "Store.h"
#include "Widget.h"

int main(int argc, char** argv) {
    /*Inizializziamo le librerie GTK+*/
    gtk_init(&argc, &argv);
    
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    gdk_threads_init();
    
    GtkWidget *window; //finestra principale
    GtkWidget *about; //finestra di about
    GtkWidget *fixed; //griglia per posizionare i widget
    GtkWidget *notebook; //notebook con tab
    
    /* Creiamo un GtkWindow di tipo widget. 
     * La window e' di tipo GTK_WINDOW_TOPLEVEL.
     * 
     * GTK_WINDOW_TOPLEVEL ha gia' barra del titolo e bordi 
     * e vengono gestiti dal Gestore Finestre di sistema.
     */
    {
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        //Imposta la posizione su schermo
        gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
        //Imposta la dimensione
        gtk_window_set_default_size(GTK_WINDOW(window), 1000, 800);
        //Imposta il titolo
        gtk_window_set_title(GTK_WINDOW(window), "Gestione Borsa");
        //Imposta icona finestra
        gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("images/money.png"));
        //Imposta il bordo tra la finetra ed il suo contenuto
        gtk_container_set_border_width(GTK_CONTAINER(window), 10);
        //Imposta l'impossibilita' di ridimensionare la finestra
        gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    }
    fixed = gtk_fixed_new(); //container della finestra
    
    /* Notebook con le tab*/
    notebook = gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_BOTTOM);
    gtk_fixed_put(GTK_FIXED(fixed), notebook, 0, 0);
    gtk_widget_set_size_request(notebook, 710, 510);
    {
        
        GtkWidget *World_container;
            
        { /*Tab del World*/
            GtkWidget *World_label;
            GtkWidget *map;
            
            World_container = gtk_fixed_new();
            World_label = create_notebook_label("World", GTK_NOTEBOOK(notebook),FALSE, 0);
            map = gtk_image_new_from_file("images/world_globe.gif");
            
            gtk_fixed_put(GTK_FIXED(World_container), map, 10, 10);
            gtk_widget_set_size_request(map, 670, 410);

            gtk_notebook_append_page(GTK_NOTEBOOK(notebook), World_container, World_label);   
        }
        //inizializzo l'azionista
        init_User(2500);
        /**
         * Creare urgentemente una struttura qui sotto per poter fare il draw realtime dei label del Actionist
         */
        { /*Tab del Profile*/
            GtkWidget *Profile_frame, *Profile_container, *Profile_label;
            
            Profile_frame = gtk_frame_new("Home");
            Profile_container = gtk_fixed_new();
            
            Actionist_Profile* actionist_home = new_Actionist_profile(get_User(),GTK_FIXED(Profile_container));
            
            GtkWidget *text = gtk_label_new("Benvenuto nella tua pagina amministrativa\n"
                    "Qui potrai amministrare le tue attivita'\n");
            
            
            gtk_container_add(GTK_CONTAINER(Profile_frame), Profile_container);
            
            gtk_fixed_put(GTK_FIXED(Profile_container),text,5,5);
/*
            gtk_fixed_put(GTK_FIXED(Profile_container),found_frame,10,60);
            gtk_fixed_put(GTK_FIXED(Profile_container),action_frame,10,150);
*/
            //inizializzo le componenti del programma tra cui le company e le comp. grafiche delle company
            //init_all_Company();
            //init_all_Company_exposer(GTK_NOTEBOOK(notebook), window);
            //init_all_Action(GTK_FIXED(actionist_home->action_container));
            INIT_ALL(GTK_NOTEBOOK(notebook),GTK_FIXED(actionist_home->action_container), window);
            
            Profile_label = create_notebook_label("Profile", GTK_NOTEBOOK(notebook),FALSE, 9);
            gtk_notebook_append_page(GTK_NOTEBOOK(notebook), Profile_frame, Profile_label);
            
            //g_idle_add_full(G_PRIORITY_DEFAULT_IDLE, (GSourceFunc) update_actionist_profile_draw, (gpointer) actionist_home, NULL);
            actionist_home->idle = pthread_create(&actionist_home->thread,NULL,update_actionist_profile_draw,(void *) actionist_home);
        }
        
        
        
        { /*Oggi inerenti alle company*/
            gtk_fixed_put(GTK_FIXED(World_container),get_Company_exposer(0)->button, 100,100);
            
            gtk_fixed_put(GTK_FIXED(World_container),get_Company_exposer(1)->button, 100,170);
            
            gtk_fixed_put(GTK_FIXED(World_container),get_Company_exposer(2)->button, 100,240);
            
            gtk_fixed_put(GTK_FIXED(World_container),get_Company_exposer(3)->button, 400,100);
            
            gtk_fixed_put(GTK_FIXED(World_container),get_Company_exposer(4)->button, 400,170);
            
            gtk_fixed_put(GTK_FIXED(World_container),get_Company_exposer(5)->button, 400,240);
            
        }
        
        
    }
    
    /* Bottoni vari */
    about = gtk_button_new_with_label("About");//aggiunge il bottone di about
    gtk_fixed_put(GTK_FIXED(fixed), about, 630, 505);
    gtk_widget_set_size_request(about, 80, 35);
    //Azione alla pressione del bottone
    g_signal_connect(G_OBJECT(about), "clicked", 
      G_CALLBACK(show_about), G_OBJECT(window));
    
    /* Powerd by gtk :D*/
    {
      GtkWidget *gtk = gtk_image_new_from_file("images/gtk-banner.png"); 
      GtkWidget *text = gtk_label_new("Powered by");
      gtk_fixed_put(GTK_FIXED(fixed), text, 0, 520);
      gtk_fixed_put(GTK_FIXED(fixed), gtk, 87, 525);
      gtk_widget_show(gtk);
      gtk_widget_show(text);
    }
    
    gtk_container_add(GTK_CONTAINER(window), fixed);
      
    /*--------------------------------------------------------
    * La seguente funzione aggiorna di continuo lo stato dei plot
    * in particolare la renderizzazione tramite evento
    *------------------------------------------------------*/
    g_idle_add_full(G_PRIORITY_DEFAULT_IDLE, (GSourceFunc) update_graph_draw, (gpointer) notebook, NULL);
      
    //Mostra tutti i windget della finestra
    gtk_widget_show_all(window);
    
    //Evento della window per distrugerla quando viene chiusa e tutti i dati allocati precedentemente
    g_signal_connect(window, "destroy", 
      G_CALLBACK (exit_Application), NULL);
    /*
     * Mandiamo in esecuzione le gtk
     */
    gtk_main();
}
