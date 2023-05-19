#include <gtk/gtk.h>

// Callback function to be called when the button is clicked
void on_button_clicked(GtkButton button, gpointer user_data) {
    g_print("Button clicked!\n");
}

int main(int argc, charargv[]) {
    GtkWidget window;
    GtkBuilderbuilder;
    GObject *button;

    // Initialize GTK
    gtk_init(&argc, &argv);

    // Load the Glade file
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "../editor_glade.glade", NULL);

    // Get a reference to the button widget
    button = gtk_builder_get_object(builder, "delete_button");

    // Connect the button's "clicked" signal to the callback function
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);

    // Create the window and set its properties
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);

    // Show the window and run the main GTK loop
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
