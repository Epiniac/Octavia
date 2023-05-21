#include <gtk/gtk.h>
#include "download.c"
#include "delete.c"

int main(int argc, char* argv[]) {
    // Initialize GTK                                                                                                                                                                 
    gtk_init(&argc, &argv);

    // Load your Glade interface                                                                                                                                                      
    GtkBuilder* builder = gtk_builder_new_from_file("../editor.glade");
    GtkWidget* window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    GtkWidget* download = GTK_WIDGET(gtk_builder_get_object(builder, "download_button"));
    GtkWidget *delete_button = GTK_WIDGET(gtk_builder_get_object(builder, "delete_button"));
    GtkWidget *box1 = GTK_WIDGET(gtk_builder_get_object(builder, "box1"));
    GtkWidget *box2 = GTK_WIDGET(gtk_builder_get_object(builder, "box2"));
    GtkWidget *box3 = GTK_WIDGET(gtk_builder_get_object(builder, "box3"));
    GtkWidget *box4 = GTK_WIDGET(gtk_builder_get_object(builder, "box4"));

    // Perform any necessary modifications to the interface                                                                                                                           
    g_signal_connect(download, "clicked", G_CALLBACK(download_button), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(delete_button, "clicked", G_CALLBACK(activate_delete),FALSE);
    g_signal_connect(box1, "button-press-event", G_CALLBACK(on_image_button_press), NULL);
    g_signal_connect(box2, "button-press-event", G_CALLBACK(on_image_button_press), NULL);
    g_signal_connect(box3, "button-press-event", G_CALLBACK(on_image_button_press), NULL);
    g_signal_connect(box4, "button-press-event", G_CALLBACK(on_image_button_press), NULL);


    g_object_unref(builder);
    gtk_widget_show(window);
    gtk_main();

    return 0;
}

