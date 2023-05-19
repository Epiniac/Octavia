#include <gtk/gtk.h>

// Callback function to be called when the button is clicked
void delete_image(GtkButton button, gpointer user_data) {
    g_print("Button clicked!\n");
    
}

int main(int argc, char **argv)
{
    GtkWidget *window;
    GtkBuilder *builder;
    GObject *button;

    // Initialize GTK
    gtk_init(&argc, &argv);

    // Load the Glade file
    builder = gtk_builder_new_from_file("../editor.glade");

    // Get a reference to the button widget
    button = gtk_builder_get_object(builder, "delete_button");

    // Connect the button's "clicked" signal to the callback function
    g_signal_connect(button, "clicked", G_CALLBACK(delete_image), NULL);

    // Create the window and set its properties
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);

    // Show the window and run the main GTK loop
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
