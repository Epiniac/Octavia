#include <gtk/gtk.h>
#include "buttons_codes_copy/download.h"
#include "buttons_codes_copy/delete.h"
#include "buttons_codes_copy/new.h"
#include "buttons_codes_copy/quit.h"
#include "buttons_codes_copy/convert.h"
#include "buttons_codes_copy/record.h"
#include <gst/gst.h>


//#include "Editor/conv.h"

int main(int argc, char* argv[]) {
    // Initialize GTK                                                                                                                                                                 
    gtk_init(&argc, &argv);
    gst_init(&argc, &argv);

    // Créez les éléments du pipeline
    pipeline = gst_pipeline_new("audio-recording");
    source = gst_element_factory_make("autoaudiosrc", "audio-source");
    encoder = gst_element_factory_make("wavenc", "audio-encoder");
    sink = gst_element_factory_make("filesink", "file-sink");

    if (!pipeline || !source || !encoder || !sink)
    {
        g_printerr("Impossible de créer les éléments du pipeline.\n");
	return -1;
    }

    // Ajoutez les éléments au pipeline
    gst_bin_add_many(GST_BIN(pipeline), source, encoder, sink, NULL);

    // Liez les éléments dans le pipeline
    if (!gst_element_link_many(source, encoder, sink, NULL))
    {
        g_printerr("Impossible de lier les éléments du pipeline.\n");
        gst_object_unref(GST_OBJECT(pipeline));
        return -1;
    }
    // Load your Glade interface                                                                                                                                                      
    GtkBuilder* builder = gtk_builder_new_from_file("editor.glade");
    GtkWidget* window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    GtkWidget* download = GTK_WIDGET(gtk_builder_get_object(builder, "download_button"));
    GtkWidget *delete_button = GTK_WIDGET(gtk_builder_get_object(builder, "delete_button"));
    GtkWidget *new_button = GTK_WIDGET(gtk_builder_get_object(builder, "new_button"));
    GtkWidget *fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));
    add_blanches = GTK_WIDGET(gtk_builder_get_object(builder, "add_blanches"));
    add_croche = GTK_WIDGET(gtk_builder_get_object(builder, "add_croche"));
    add_4 = GTK_WIDGET(gtk_builder_get_object(builder,"add_4"));
    add_noires = GTK_WIDGET(gtk_builder_get_object(builder,"add_noires"));
    GtkWidget *quit = GTK_WIDGET(gtk_builder_get_object(builder, "quit"));
    GtkFileChooserButton *convert_button = GTK_WIDGET(gtk_builder_get_object(builder, "convert_button"));
    GtkWidget *np_button = GTK_WIDGET(gtk_builder_get_object(builder, "np_button"));
    GtkWidget *stop_button = GTK_WIDGET(gtk_builder_get_object(builder, "STOP"));

    // Perform any necessary modifications to the interface                                                                                                                           
    g_signal_connect(download, "clicked", G_CALLBACK(download_button), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(delete_button, "clicked", G_CALLBACK(activate_delete),FALSE);
    g_signal_connect(new_button, "clicked", G_CALLBACK(new_partition), fixed);
    g_signal_connect(add_blanches, "clicked", G_CALLBACK(load_image),fixed);
    g_signal_connect(add_croche, "clicked", G_CALLBACK(load_image),fixed);
    g_signal_connect(add_4, "clicked", G_CALLBACK(load_image),fixed);
    g_signal_connect(add_noires, "clicked", G_CALLBACK(load_image),fixed);
    g_signal_connect(window, "button-press-event", G_CALLBACK(print_image), fixed);
    g_signal_connect(quit, "clicked", G_CALLBACK(on_button_clicked),window);
    g_signal_connect(convert_button, "file-set", G_CALLBACK(file_selected), fixed);
    g_signal_connect(stop_button, "clicked", G_CALLBACK(arreterEnregistrement), NULL);
    g_signal_connect(np_button, "clicked", G_CALLBACK(rec), NULL);


    g_object_unref(builder);
    gtk_widget_show(window);
    gtk_main();

    return 0;
}
