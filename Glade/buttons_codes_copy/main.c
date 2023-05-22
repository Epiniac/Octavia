#include <gtk/gtk.h>
#include "download.c"
#include "delete.c"
#include "new.c"
#include "quit.c"


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
    GtkWidget *new_button = GTK_WIDGET(gtk_builder_get_object(builder, "new_button"));
    GtkWidget *fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));
    add_blanches = GTK_WIDGET(gtk_builder_get_object(builder, "add_blanches"));
    add_croche = GTK_WIDGET(gtk_builder_get_object(builder, "add_croche"));
    add_4 = GTK_WIDGET(gtk_builder_get_object(builder,"add_4"));
    add_noires = GTK_WIDGET(gtk_builder_get_object(builder,"add_noires"));
    GtkWidget *quit = GTK_WIDGET(gtk_builder_get_object(builder, "quit"));
    
    // Perform any necessary modifications to the interface                                                                                                                           
    g_signal_connect(download, "clicked", G_CALLBACK(download_button), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(delete_button, "clicked", G_CALLBACK(activate_delete),FALSE);
    g_signal_connect(box1, "button-press-event", G_CALLBACK(on_image_button_press), NULL);
    g_signal_connect(box2, "button-press-event", G_CALLBACK(on_image_button_press), NULL);
    g_signal_connect(box3, "button-press-event", G_CALLBACK(on_image_button_press), NULL);
    g_signal_connect(box4, "button-press-event", G_CALLBACK(on_image_button_press), NULL);
    g_signal_connect(new_button, "clicked", G_CALLBACK(new_partition), fixed);
    g_signal_connect(add_blanches, "clicked", G_CALLBACK(load_image),fixed);
    g_signal_connect(add_croche, "clicked", G_CALLBACK(load_image),fixed);
    g_signal_connect(add_4, "clicked", G_CALLBACK(load_image),fixed);
    g_signal_connect(add_noires, "clicked", G_CALLBACK(load_image),fixed);
    g_signal_connect(window, "button-press-event", G_CALLBACK(print_image), fixed);
    g_signal_connect(quit, "clicked", G_CALLBACK(on_button_clicked),window);




    g_object_unref(builder);
    gtk_widget_show(window);
    gtk_main();

    return 0;
}

