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
            "Si veda la licenza GNU General Public License per maggiori dettagli.\n"
            "\nSi ringrazia la GNOME Foundation per le bellissime librerie GTK.");
    gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(dialog),&author);
    g_object_unref(image), image = NULL;
    gtk_dialog_run(GTK_DIALOG (dialog));
    gtk_widget_destroy(dialog);

}

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
    
    //gtk_databox_set_total_limits(GTK_DATABOX(databox),0,POINTS,100,-100);
    gtk_databox_auto_rescale(GTK_DATABOX(databox), 0.05);
    
    gtk_widget_show_all(databoxcontainer);

    return(databoxcontainer);
}

GtkWidget * create_company_frame_graph(Company* Company_n, GtkWidget *Company_graph, gpointer window){
    GtkWidget *Company_frame = gtk_frame_new("Company");
    GtkWidget *Company_container = gtk_fixed_new();
    {
        GtkWidget *Company_frame_info = gtk_frame_new("Info");
        gtk_frame_set_shadow_type(GTK_FRAME(Company_frame_info), GTK_SHADOW_IN);
        
        GtkWidget *Company_info_container = gtk_fixed_new();
        GtkWidget *Company_info_template = gtk_label_new("Nome:\n"
                "Tipo:                                          Valor Medio:\nFound:                                          Stato:"
                "");
        GtkWidget *Company_info_name = gtk_label_new(Company_n->name);
        GtkWidget *Company_info_type = gtk_label_new(type2Text(Company_n->type));
        GtkWidget *Company_info_found = gtk_label_new(float2Text(Company_n->found));
        GtkWidget *Company_info_midvalue = gtk_label_new(float2Text(Value_midrange(Company_n)));
        
        gtk_fixed_put(GTK_FIXED(Company_info_container),Company_info_template,5,1);
        gtk_fixed_put(GTK_FIXED(Company_info_container),Company_info_name,50,1);
        gtk_fixed_put(GTK_FIXED(Company_info_container),Company_info_type,50,15);
        gtk_fixed_put(GTK_FIXED(Company_info_container),Company_info_found,50,31);
        gtk_fixed_put(GTK_FIXED(Company_info_container),Company_info_midvalue,300,15);

        gtk_container_add(GTK_CONTAINER(Company_frame_info),Company_info_container);
        gtk_widget_set_size_request(Company_frame_info,350,80);
        gtk_fixed_put(GTK_FIXED(Company_container),Company_frame_info,2,2);
        
        GtkWidget *Buy_button = gtk_button_new_with_label("Compra Azioni");
        GtkWidget *Sell_button = gtk_button_new_with_label("Vendi Azioni");

        gtk_widget_set_usize(GTK_WIDGET(Buy_button),180,40);
        gtk_widget_set_usize(GTK_WIDGET(Sell_button),180,40);
        
        g_signal_connect(G_OBJECT(Buy_button), "clicked", 
                        G_CALLBACK(Buy), (gpointer) window);
        g_signal_connect(G_OBJECT(Sell_button), "clicked", 
                        G_CALLBACK(Sell), (gpointer) window);

        gtk_fixed_put(GTK_FIXED(Company_container),Buy_button, 430,5);
        gtk_fixed_put(GTK_FIXED(Company_container),Sell_button, 430,45);
    }   
    
    gtk_fixed_put(GTK_FIXED(Company_container),Company_graph,5,105);
    gtk_widget_set_size_request(Company_graph,680,320);

    gtk_container_add(GTK_CONTAINER(Company_frame), Company_container);
    
    return Company_frame;
}

GtkWidget * create_company_frame(Company* Company_n){
    GtkWidget *Company_frame = gtk_frame_new("Company");
    GtkWidget *Company_container = gtk_fixed_new();
    {
        GtkWidget *Company_frame_info = gtk_frame_new("Info");
        gtk_frame_set_shadow_type(GTK_FRAME(Company_frame_info), GTK_SHADOW_IN);
        
        GtkWidget *Company_info_container = gtk_fixed_new();
        GtkWidget *Company_info_template = gtk_label_new("Nome:\nTipo:\nFound:");
        GtkWidget *Company_info_name = gtk_label_new(Company_n->name);
        GtkWidget *Company_info_type = gtk_label_new(type2Text(Company_n->type));
        GtkWidget *Company_info_found = gtk_label_new(float2Text(Company_n->found));

        gtk_fixed_put(GTK_FIXED(Company_info_container),Company_info_template,5,1);
        gtk_fixed_put(GTK_FIXED(Company_info_container),Company_info_name,50,1);
        gtk_fixed_put(GTK_FIXED(Company_info_container),Company_info_type,50,15);
        gtk_fixed_put(GTK_FIXED(Company_info_container),Company_info_found,50,31);

        gtk_container_add(GTK_CONTAINER(Company_frame_info),Company_info_container);
        gtk_widget_set_size_request(Company_frame_info,350,80);
        gtk_fixed_put(GTK_FIXED(Company_container),Company_frame_info,5,5);
        
        GtkWidget *Buy_button = gtk_button_new_with_label("Compra Azioni");
        GtkWidget *Sell_button = gtk_button_new_with_label("Vendi Azioni");
        
        gtk_widget_set_usize(GTK_WIDGET(Buy_button),180,40);
        gtk_widget_set_usize(GTK_WIDGET(Sell_button),180,40);
        
        g_signal_connect(G_OBJECT(Buy_button), "Buy", 
                        G_CALLBACK(Buy), NULL);
        g_signal_connect(G_OBJECT(Sell_button), "Sell", 
                        G_CALLBACK(Sell), NULL);
        
        gtk_fixed_put(GTK_FIXED(Company_container),Buy_button, 430,5);
        gtk_fixed_put(GTK_FIXED(Company_container),Sell_button, 430,45);
        
    }   
    GtkWidget *Company_graph = create_graph_with_rules(Company_n->x,Company_n->y, POINTS );
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