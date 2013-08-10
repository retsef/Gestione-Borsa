#include "Gtk_Notebook.h"
#include <stdbool.h>
#include <gtk/gtk.h>
#include <gtkdatabox_typedefs.h>

/**
 * Crea un tab per il notebook avente il bottone di chiusura
 * @param text Testo sulla linghuetta della tab
 * @param notebook Notebook a cui affiliare la tab
 * @param cloosable Se si vuole rendere la tab chiudibile
 * @param page Indice di tab
 * @return GtkWidget per il notebook
 */
GtkWidget * create_notebook_label(const gchar *text, GtkNotebook *notebook, bool cloosable, int page){
    GtkWidget *hbox,*label,*button,*image;
    
    /*Il widget hbox disporra' l'intestazione del label e il close button in un unica riga*/
    hbox = gtk_hbox_new (FALSE, 3); 

    label = gtk_label_new (text);
    gtk_box_pack_start (GTK_BOX(hbox), label, TRUE, TRUE, 0);

    if(cloosable){
        button = gtk_button_new();
        g_object_set_data(G_OBJECT(button), "page", GINT_TO_POINTER(page));
            g_signal_connect(G_OBJECT(button), "clicked",
                         G_CALLBACK(cb_close_tab),
                         GTK_NOTEBOOK(notebook));
        gtk_box_pack_start (GTK_BOX(hbox), button, FALSE, FALSE, 0);
        image = gtk_image_new_from_stock (GTK_STOCK_CLOSE, GTK_ICON_SIZE_MENU);
        gtk_container_add (GTK_CONTAINER(button), image);
        gtk_button_set_relief (GTK_BUTTON(button), GTK_RELIEF_NONE);
    }

    gtk_widget_show_all( hbox );

    return( hbox );
}
/**
 * Funzione che interviene alla chiusura della tab
 * @param button Bottone "x" sulla tab
 * @param notebook Notebook a cui la tab e' ancorata
 */
static void cb_close_tab(GtkButton *button, GtkNotebook *notebook ){
    int page;

    page = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "page"));
    gtk_notebook_remove_page(notebook, page);
}

/**
 * Crea un pixbuf(buffer di pixel) per processare immagini
 * @param filename file immagine
 * @return un nuovo pixbuf
 */
GdkPixbuf *create_pixbuf(const gchar * filename){
    
    static GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    if(!pixbuf) {
       fprintf(stderr, "%s\n", error->message);
       g_error_free(error);
    }

    return pixbuf;
}

GtkWidget * create_graph_with_rules(GtkWidget *container, gfloat x, gfloat y, int graph_lenght){
    GtkDatabox *databox;
    GtkWidget *databoxcontainer;
    
    gtk_databox_create_box_with_scrollbars_and_rulers (
        databox, databoxcontainer,
        TRUE, TRUE, TRUE, TRUE);

    //const int grlen = 5;
    //gfloat x[] = { 1 , 2,   3,  4,   5, 0 };
    //gfloat y[] = { 4 , 5, 7.5, 11, 4.3, 0 };
    GdkColor markerColor = { 0, 65000, 0, 0 };
    GtkDataboxGraph *graph = gtk_databox_lines_new(graph_lenght, x, y, &markerColor, 1 );
    gtk_databox_graph_add (databox, graph);
    gtk_databox_auto_rescale (databox, 0.05);
}
