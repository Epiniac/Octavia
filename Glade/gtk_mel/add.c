#include <gtk/gtk.h>

GtkWidget *main_window;
GtkWidget *image_blanche;
GtkWidget *image_noires;
GtkWidget *image_croche;
GtkWidget *image_croches;
GtkWidget *add_blanches;
GtkWidget *add_noires;
GtkWidget *add_croche;
GtkWidget *add_4;

void on_button_clicked(GtkButton *button, gpointer user_data) {
    if (button == GTK_BUTTON(add_blanches)) {
        gtk_image_set_from_file(GTK_IMAGE(image_blanche), "../images/images_notes/note_blanche.png");
    } else if (button == GTK_BUTTON(add_noires)) {
        gtk_image_set_from_file(GTK_IMAGE(image_noires), "../images/images_notes/note_noires.png");
    } else if (button == GTK_BUTTON(add_croche)) {
        gtk_image_set_from_file(GTK_IMAGE(image_croche), "../images/images_notes/note_croche.png");
    } else if (button == GTK_BUTTON(add_4)) {
        gtk_image_set_from_file(GTK_IMAGE(image_croches), "../images/images_notes/note_croches.png");
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkBuilder *builder = gtk_builder_new_from_file("../editor.glade");

    main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    image_blanche = GTK_WIDGET(gtk_builder_get_object(builder, "image_blanche"));
    image_noires = GTK_WIDGET(gtk_builder_get_object(builder, "image_noires"));
    image_croche = GTK_WIDGET(gtk_builder_get_object(builder, "image_croche"));
    image_croches = GTK_WIDGET(gtk_builder_get_object(builder, "image_croches"));
    add_blanches = GTK_WIDGET(gtk_builder_get_object(builder, "add_blanches"));
    add_noires = GTK_WIDGET(gtk_builder_get_object(builder, "add_noires"));
    add_croche = GTK_WIDGET(gtk_builder_get_object(builder, "add_croche"));
    add_4 = GTK_WIDGET(gtk_builder_get_object(builder, "add_4"));

    g_signal_connect(add_blanches, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(add_noires, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(add_croche, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(add_4, "clicked", G_CALLBACK(on_button_clicked), NULL);

    g_object_unref(builder);

    gtk_widget_show(main_window);
    gtk_main();

    return 0;
}

