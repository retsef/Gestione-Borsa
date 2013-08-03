#include "Gtk_Notebook.h"
#include <stdbool.h>
#include <gtk/gtk.h>

GtkWidget * create_notebook_label(const gchar *text, GtkWidget *notebook, bool cloosable, int page){
    GtkWidget *hbox,*label,*button,*image;
    
    hbox = gtk_hbox_new (FALSE, 3);

    label = gtk_label_new (text);
    gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);

    if(cloosable){
        button = gtk_button_new();
        g_object_set_data( G_OBJECT( button ), "page", GINT_TO_POINTER( page ) );
            g_signal_connect( G_OBJECT( button ), "clicked",
                         G_CALLBACK( cb_close_tab ),
                         GTK_NOTEBOOK( notebook ) );
        gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, FALSE, 0);
        image = gtk_image_new_from_stock (GTK_STOCK_CLOSE, GTK_ICON_SIZE_MENU);
        gtk_container_add (GTK_CONTAINER (button), image);
    }

    gtk_widget_show_all( hbox );

    return( hbox );
}

static void cb_close_tab(GtkButton *button,GtkNotebook *notebook ){
    int page;

    page = GPOINTER_TO_INT( g_object_get_data( G_OBJECT( button ), "page" ) );
    gtk_notebook_remove_page( notebook, page );
}

/**
 * Crea un pixbuf(buffer di pixel) per processare immagini
 * @param filename file immagine
 * @return un nuovo pixbuf
 */
GdkPixbuf *create_pixbuf(const gchar * filename){
    
    GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    if(!pixbuf) {
       fprintf(stderr, "%s\n", error->message);
       g_error_free(error);
    }

    return pixbuf;
}
