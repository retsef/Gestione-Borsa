#include "Gtk_Widget.h"
#include "Background.h"
#include <stdbool.h>
#include <gtk/gtk.h>
#include <gtkdatabox.h>
#include <gtkdatabox_points.h>
#include <gtkdatabox_lines.h>

static GtkWidget *Company_frame;
static GtkWidget *Company_label;

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

    gtk_widget_show_all(hbox);

    return(hbox);
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
/**
 * Crea un Grafico (GtkDataBox) e lo attacca ad un Container
 * @param container Container su cui appiccicare il grafico
 * @param x Array di numeri per la X
 * @param y Array di numeri per la Y
 * @param graph_lenght Lunghezza del grafico
 * @return Un GtkWidget contenente il grafico
 */
GtkWidget * create_graph_with_rules(gfloat *x, gfloat *y, int graph_lenght){    
    GtkWidget *databox;
    GtkWidget *databoxcontainer;
    GtkDataboxGraph *graph;
    
    //gtk_box_pack_start(GTK_BOX(container), databoxcontainer, 1, 1, 0 );
    
    gtk_databox_create_box_with_scrollbars_and_rulers(
        &databox, &databoxcontainer, 
            FALSE, FALSE, TRUE, TRUE);

    GdkColor markerColor = { 0, 65000, 0, 0 };
    //errore qui poiche' non vi e' un passaggio di riferimento tra tipi ma tra puntatori
    graph = gtk_databox_lines_new(graph_lenght, x, y, &markerColor, 1);
    gtk_databox_graph_add(GTK_DATABOX(databox), graph);
    gtk_databox_auto_rescale(GTK_DATABOX(databox), 0.05);
    
    gtk_widget_show_all(databoxcontainer);

    return(databoxcontainer);
}

GtkWidget * create_company_frame_graph(Company Company_n, GtkWidget *Company_graph){
    GtkWidget *Company_frame = gtk_frame_new("Company");
    GtkWidget *Company_container = gtk_fixed_new();
    {
        GtkWidget *Company_frame_info = gtk_frame_new("Info");
        gtk_frame_set_shadow_type(GTK_FRAME(Company_frame_info), GTK_SHADOW_IN);
        
        GtkWidget *Company_info_container = gtk_fixed_new();
        GtkWidget *Company_info_template = gtk_label_new("Nome:\nTipo:\nFound:");
        GtkWidget *Company_info_name = gtk_label_new(Company_n.name);
        GtkWidget *Company_info_type = gtk_label_new(type2Text(Company_n.type));
        GtkWidget *Company_info_found = gtk_label_new(found2Text(Company_n.found));

        gtk_fixed_put(GTK_FIXED(Company_info_container),Company_info_template,5,1);
        gtk_fixed_put(GTK_FIXED(Company_info_container),Company_info_name,50,1);
        gtk_fixed_put(GTK_FIXED(Company_info_container),Company_info_type,50,15);
        gtk_fixed_put(GTK_FIXED(Company_info_container),Company_info_found,50,31);

        gtk_container_add(GTK_CONTAINER(Company_frame_info),Company_info_container);
        gtk_widget_set_size_request(Company_frame_info,350,80);
        gtk_fixed_put(GTK_FIXED(Company_container),Company_frame_info,5,5);
    }   
    
    gtk_fixed_put(GTK_FIXED(Company_container),Company_graph,5,105);
    gtk_widget_set_size_request(Company_graph,680,320);

    gtk_container_add(GTK_CONTAINER(Company_frame), Company_container);
    
    return Company_frame;
}

GtkWidget * create_company_frame(Company Company_n){
    GtkWidget *Company_frame = gtk_frame_new("Company");
    GtkWidget *Company_container = gtk_fixed_new();
    {
        GtkWidget *Company_frame_info = gtk_frame_new("Info");
        gtk_frame_set_shadow_type(GTK_FRAME(Company_frame_info), GTK_SHADOW_IN);
        
        GtkWidget *Company_info_container = gtk_fixed_new();
        GtkWidget *Company_info_template = gtk_label_new("Nome:\nTipo:\nFound:");
        GtkWidget *Company_info_name = gtk_label_new(Company_n.name);
        GtkWidget *Company_info_type = gtk_label_new(type2Text(Company_n.type));
        GtkWidget *Company_info_found = gtk_label_new(found2Text(Company_n.found));

        gtk_fixed_put(GTK_FIXED(Company_info_container),Company_info_template,5,1);
        gtk_fixed_put(GTK_FIXED(Company_info_container),Company_info_name,50,1);
        gtk_fixed_put(GTK_FIXED(Company_info_container),Company_info_type,50,15);
        gtk_fixed_put(GTK_FIXED(Company_info_container),Company_info_found,50,31);

        gtk_container_add(GTK_CONTAINER(Company_frame_info),Company_info_container);
        gtk_widget_set_size_request(Company_frame_info,350,80);
        gtk_fixed_put(GTK_FIXED(Company_container),Company_frame_info,5,5);
    }   
    GtkWidget *Company_graph = create_graph_with_rules(Company_n.x,Company_n.y, POINTS );
    gtk_fixed_put(GTK_FIXED(Company_container),Company_graph,5,105);
    gtk_widget_set_size_request(Company_graph,680,320);

    gtk_container_add(GTK_CONTAINER(Company_frame), Company_container);
    
    return Company_frame;
}

void create_company_tab(GtkButton *button, GtkWidget *array[]){
    /*
    GtkWidget *Company0_label = create_notebook_label(get_Company_by_name(gtk_button_get_label(button)).name, GTK_NOTEBOOK(notebook),TRUE, 1);
    GtkWidget *Company0_frame = create_company_frame(get_Company_by_name(gtk_button_get_label(button)));
    */
    /*
    gtk_notebook_insert_page(GTK_NOTEBOOK(data->notebook), data->frame, data->label,1);
    gtk_widget_show_all(data->notebook);
    
    gtk_notebook_set_current_page(GTK_NOTEBOOK(data->notebook),1);
    */
    gtk_notebook_insert_page(GTK_NOTEBOOK(array[2]), array[0], array[1],1);
    gtk_widget_show_all(array[2]);
    
    gtk_notebook_set_current_page(GTK_NOTEBOOK(array[2]),1);
}