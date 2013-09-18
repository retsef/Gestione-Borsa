/* 
 * File:   main.c
 * Author: roberto
 *
 * Created on 28 luglio 2013, 16.14
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <gtk/gtk.h>

#include "Gtk_Widget.h"
#include "Background.h"

/*
#include <pthread.h>
*/

main( int argc, char *argv[]){
    
    /*
     * Inizializziamo le librerie GTK+
     */
    gtk_init(&argc, &argv);
    
    GtkWidget *window; //finestra principale
    GtkWidget *about; //finestra di about
    
    GtkWidget *fixed; //griglia per posizionare i widget
    
    GtkWidget *notebook;
    GtkWidget *World_frame,*Profile_frame;
    GtkWidget *World_label,*Profile_label;
    /*
     * Inizializziamo le librerie GTK+
     */
    gtk_init(&argc, &argv);
    
    /*
     * Creiamo un GtkWindow di tipo widget. 
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
        gtk_container_set_border_width(GTK_CONTAINER(window), 3);
        //Imposta l'impossibilita' di ridimensionare la finestra
        gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    }
    
    fixed = gtk_fixed_new(); //container del bottone
    
    /* Notebook con le tab*/
    notebook = gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_BOTTOM);
    gtk_fixed_put(GTK_FIXED(fixed), notebook, 10, 10);
    gtk_widget_set_size_request(notebook, 700, 500);

    {
        { /*Tab del World*/
            World_frame = gtk_frame_new("Nation Exposer");
            gtk_widget_show(World_frame);
            
            GtkWidget *World_container = gtk_fixed_new();

            GtkWidget *map = gtk_image_new_from_file("images/world_red_cntry_globe_hammer.gi.gif");
            //GtkWidget *text = gtk_label_new("Qui andra' una cartina contenente \n"
            //        "i vari titoli azionari (cliccabili)");
            gtk_container_add(GTK_CONTAINER(World_frame), World_container);
            gtk_fixed_put(GTK_FIXED(World_container), map, 10, 10);
            gtk_widget_set_size_request(map, 670, 410);
            //gtk_fixed_put(GTK_FIXED(World_container), text, 250, 200);

            World_label = create_notebook_label("World", GTK_NOTEBOOK(notebook),FALSE, 0);
            gtk_notebook_append_page(GTK_NOTEBOOK(notebook), World_frame, World_label);
            
            {   
                //inizializziamo i dati delle company
                init_company();
                
                {
                    //bottone
                    GtkWidget *Company0_button;
                    Company0_button = gtk_button_new_with_label(get_Company(0)->name);
                    gtk_fixed_put(GTK_FIXED(World_container),Company0_button, 100,100);
                    
                    GtkWidget *Company0_graph = create_graph_with_rules(get_Company(0)->x,get_Company(0)->y, POINTS );
                    GtkWidget *Company0_label = create_notebook_label(get_Company(0)->name, GTK_NOTEBOOK(notebook),TRUE, 1);
                    GtkWidget *Company0_frame = create_company_frame_graph(get_Company(0),Company0_graph, (gpointer) window);
                    //GtkWidget *Company0_frame = create_company_frame(get_Company(0));
                    /*
                    Data_notebook *data0 = new_data_notebook();
                    
                    data0->frame = Company0_frame;
                    data0->label = Company0_label;
                    data0->notebook = notebook;
                    */            
                    GtkWidget *data0[3];
                    data0[0] = Company0_frame;
                    data0[1] = Company0_label;
                    data0[2] = notebook;
                    
                    //evento
                    g_signal_connect(G_OBJECT(Company0_button), "clicked", 
                        (GtkSignalFunc)create_company_tab, data0);
                    
                }
                {
                    //bottone
                    GtkWidget *Company1_button;
                    Company1_button = gtk_button_new_with_label(get_Company(1)->name);
                    gtk_fixed_put(GTK_FIXED(World_container),Company1_button, 100,170);
                    
                    GtkWidget *Company1_graph = create_graph_with_rules(get_Company(1)->x,get_Company(1)->y, POINTS );
                    GtkWidget *Company1_label = create_notebook_label(get_Company(1)->name, GTK_NOTEBOOK(notebook),TRUE, 1);
                    GtkWidget *Company1_frame = create_company_frame_graph(get_Company(1),Company1_graph, (gpointer) window);
                    
                    GtkWidget *data1[3];
                    data1[0] = Company1_frame;
                    data1[1] = Company1_label;
                    data1[2] = notebook;
                    
                    //evento
                    g_signal_connect(G_OBJECT(Company1_button), "clicked", 
                        (GtkSignalFunc)create_company_tab, data1);
                }
                {
                    //bottone
                    GtkWidget *Company2_button;
                    Company2_button = gtk_button_new_with_label(get_Company(2)->name);
                    gtk_fixed_put(GTK_FIXED(World_container),Company2_button, 100,240);
                    
                    GtkWidget *Company2_graph = create_graph_with_rules(get_Company(2)->x,get_Company(2)->y, POINTS );
                    GtkWidget *Company2_label = create_notebook_label(get_Company(2)->name, GTK_NOTEBOOK(notebook),TRUE, 1);
                    GtkWidget *Company2_frame = create_company_frame_graph(get_Company(2),Company2_graph, (gpointer) window);
                    /*
                    Data_notebook *data2 = new_data_notebook();
                    
                    data2->frame = Company2_frame;
                    data2->label = Company2_label;
                    data2->notebook = notebook;
                    */
                    GtkWidget *data2[3];
                    data2[0] = Company2_frame;
                    data2[1] = Company2_label;
                    data2[2] = notebook;
                    
                    //evento
                    g_signal_connect(G_OBJECT(Company2_button), "clicked", 
                        (GtkSignalFunc)create_company_tab, data2);
                }
                {
                    //bottone
                    GtkWidget *Company3_button;
                    Company3_button = gtk_button_new_with_label(get_Company(3)->name);
                    gtk_fixed_put(GTK_FIXED(World_container),Company3_button, 400,100);
                    
                    GtkWidget *Company3_graph = create_graph_with_rules(get_Company(3)->x,get_Company(3)->y, POINTS );
                    GtkWidget *Company3_label = create_notebook_label(get_Company(3)->name, GTK_NOTEBOOK(notebook),TRUE, 1);
                    GtkWidget *Company3_frame = create_company_frame_graph(get_Company(3),Company3_graph, (gpointer) window);
                    /*
                    Data_notebook *data3 = new_data_notebook();
                    
                    data3->frame = Company3_frame;
                    data3->label = Company3_label;
                    data3->notebook = notebook;
                    */
                    GtkWidget *data3[3];
                    data3[0] = Company3_frame;
                    data3[1] = Company3_label;
                    data3[2] = notebook;
                    
                    //evento
                    g_signal_connect(G_OBJECT(Company3_button), "clicked", 
                        (GtkSignalFunc)create_company_tab, data3);
                }
                {
                    //bottone
                    GtkWidget *Company4_button;
                    Company4_button = gtk_button_new_with_label(get_Company(4)->name);
                    gtk_fixed_put(GTK_FIXED(World_container),Company4_button, 400,170);
                    
                    GtkWidget *Company4_graph = create_graph_with_rules(get_Company(4)->x,get_Company(4)->y, POINTS );
                    GtkWidget *Company4_label = create_notebook_label(get_Company(4)->name, GTK_NOTEBOOK(notebook),TRUE, 1);
                    GtkWidget *Company4_frame = create_company_frame_graph(get_Company(4),Company4_graph, (gpointer) window);
                    /*
                    Data_notebook *data4 = new_data_notebook();
                    
                    data4->frame = Company4_frame;
                    data4->label = Company4_label;
                    data4->notebook = notebook;
                    */
                    GtkWidget *data4[3];
                    data4[0] = Company4_frame;
                    data4[1] = Company4_label;
                    data4[2] = notebook;
                    
                    //evento
                    g_signal_connect(G_OBJECT(Company4_button), "clicked", 
                        (GtkSignalFunc)create_company_tab, data4);
                }
                {
                    //bottone
                    GtkWidget *Company5_button;
                    Company5_button = gtk_button_new_with_label(get_Company(5)->name);
                    gtk_fixed_put(GTK_FIXED(World_container),Company5_button, 400,240);
                    
                    GtkWidget *Company5_graph = create_graph_with_rules(get_Company(5)->x,get_Company(5)->y, POINTS );
                    GtkWidget *Company5_label = create_notebook_label(get_Company(5)->name, GTK_NOTEBOOK(notebook),TRUE, 1);
                    GtkWidget *Company5_frame = create_company_frame_graph(get_Company(5),Company5_graph, (gpointer) window);
                    /*
                    Data_notebook *data5 = new_data_notebook();
                    
                    data5->frame = Company5_frame;
                    data5->label = Company5_label;
                    data5->notebook = notebook;
                    */
                    GtkWidget *data5[3];
                    data5[0] = Company5_frame;
                    data5[1] = Company5_label;
                    data5[2] = notebook;
                    
                    //evento
                    g_signal_connect(G_OBJECT(Company5_button), "clicked", 
                        (GtkSignalFunc)create_company_tab, data5);
                }
            }
        }
        
        { /*Tab del Profile*/
            Profile_frame = gtk_frame_new("Home");
            gtk_widget_show(Profile_frame);
            
            GtkWidget *found = gtk_label_new("");
            
            GtkWidget *text = gtk_label_new("Qui andranno le informazioni relative alle azioni aquistate \n"
                    "e ai fondi disponibili, oltre alle quote di ingresso/uscita");
            gtk_container_add(GTK_CONTAINER(Profile_frame), text);
            gtk_container_add(GTK_CONTAINER(Profile_frame), found);

            Profile_label = create_notebook_label("Profile", GTK_NOTEBOOK(notebook),FALSE, 9);
            gtk_notebook_append_page(GTK_NOTEBOOK(notebook), Profile_frame, Profile_label);
        }
    }
    
    /*
     * Bottoni vari
     */
    
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
      gtk_fixed_put(GTK_FIXED(fixed), gtk, 75, 520);
      gtk_widget_show(gtk);
      gtk_widget_show(text);
    }
    
    //Mostra tutti i windget della finestra
    gtk_container_add(GTK_CONTAINER(window), fixed);
    
    gtk_widget_show_all(window); //<-- da fixare perche' mosta TUTTI i widget compresi quelli da oscurare
    
    //Evento della window per distrugerla quando viene chiusa
    g_signal_connect(window, "destroy", 
      G_CALLBACK (gtk_main_quit), NULL);
    
    /*--------------------------------------------------------
    * set function update_graph to be called whenever 
    * the program is idle
    *------------------------------------------------------*/
    g_idle_add_full(G_PRIORITY_DEFAULT_IDLE, (GSourceFunc)update, (gpointer) notebook, NULL);
    
    /* Manda la window in loop in attesa di un nuovo evento*/
    gtk_main();
    
}