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
#include "Gtk_Notebook.h"

/*
#include <pthread.h>
*/

/**
 * Crea la finestra di About
 */
void show_about(GtkWidget *widget, gpointer data){

    GdkPixbuf *image = gdk_pixbuf_new_from_file("images/money.png", NULL);
    GtkWidget *dialog = gtk_about_dialog_new();
    const gchar* author = "Roberto Scinocca\n"
    "   roberto.scinocca@gmail.com\n"
    "   http://www.github.com/retsef";
    
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),"Roberto Scinocca");
    gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog),"Gestione Borsa");
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog),"Simula i meccanismi degli azionisti");
    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), image);
    gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(dialog),
            "Gestione Borsa è software libero; è lecito redistribuirlo o modificarlo\n"
            "secondo i termini della GNU General Public License \n"
            "come pubblicata dalla Free Software Foundation;\n"
            "o la versione 2 o (a propria scelta) una versione successiva.\n\n"
            "Si veda la licenza GNU General Public License per maggiori dettagli.\n");
    gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(dialog),&author);
    g_object_unref(image), image = NULL;
    gtk_dialog_run(GTK_DIALOG (dialog));
    gtk_widget_destroy(dialog);

}

main( int argc, char *argv[]){
    
    GtkWidget *window; //finestra principale
    GtkWidget *about; //finestra di about
    
    GtkWidget *fixed; //griglia per posizionare i widget
    
    GtkWidget *notebook;
    GtkWidget *frame1,*frame2,*frame3;
    GtkWidget *label1,*label2,*label3;
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
        gtk_window_set_title(GTK_WINDOW(window), "Main");
        //Imposta icona finestra
        gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("images/money.png"));

        gtk_container_set_border_width(GTK_CONTAINER(window), 3);
        
        gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    }
    
    fixed = gtk_fixed_new(); //container del bottone
    
    /* Notebook con le tab*/
    notebook = gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_BOTTOM);
    gtk_fixed_put(GTK_FIXED(fixed), notebook, 10, 10);
    gtk_widget_set_size_request(notebook, 700, 500);
    //gtk_widget_show(notebook);

    {
        {
            frame1 = gtk_frame_new("Nation Exposer");
            gtk_widget_show(frame1);
            
            GtkWidget *fixed1 = gtk_fixed_new();

            GtkWidget *map = gtk_image_new_from_file("images/world-map.jpg");
            GtkWidget *text = gtk_label_new("Qui andra' una cartina contenente \n"
                    "i vari titoli azionari (cliccabili)");
            gtk_container_add(GTK_CONTAINER(frame1), fixed1);
            gtk_fixed_put(GTK_FIXED(fixed1), map, 10, 10);
            gtk_widget_set_size_request(map, 670, 410);
            gtk_fixed_put(GTK_FIXED(fixed1), text, 250, 200);
            //gtk_widget_show(label1);

            label1 = create_notebook_label("World", GTK_NOTEBOOK(notebook),FALSE, 0);
            gtk_notebook_append_page(GTK_NOTEBOOK(notebook), frame1, label1);
        }
        {
            frame2 = gtk_frame_new("Company");
            
            label2 = create_notebook_label("Company", GTK_NOTEBOOK(notebook),TRUE, 1);
            gtk_notebook_append_page(GTK_NOTEBOOK(notebook), frame2, label2);
        }
        {
            frame3 = gtk_frame_new("Home");
            gtk_widget_show(frame3);
            
            GtkWidget *text = gtk_label_new("Qui andranno le informazioni relative alle azioni aquistate \n"
                    "e ai fondi disponibili, oltre alle quote di ingresso/uscita");
            gtk_container_add(GTK_CONTAINER(frame3), text);
            //gtk_widget_show(label3);

            label3 = create_notebook_label("Profile", GTK_NOTEBOOK(notebook),FALSE, 2);
            gtk_notebook_append_page(GTK_NOTEBOOK(notebook), frame3, label3);
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
      gtk_fixed_put(GTK_FIXED(fixed), gtk, 80, 525);
    }
    
    //Mostra tutti i windget della finestra
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show_all(window);
    
    //Evento della window per distrugerla quando viene chiusa
    g_signal_connect(window, "destroy", 
      G_CALLBACK (gtk_main_quit), NULL);
    
    /* Manda la window in loop in attesa di un nuovo evento*/
    gtk_main();
    
}
