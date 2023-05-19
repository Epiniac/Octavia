#include <stdio.h>
#include <SDL2/SDL.h>
#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    // ...

    // Chargement de l'interface Glade
    GtkBuilder *builder;
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "editor.glade", NULL);

    GtkWidget *window;
    window = GTK_WIDGET(gtk_builder_get_object(builder,"menu")
   
   //initialisation boutons des notes:
   GtkWidget *add_blanches;
   add_blanches = GTK_WIDGET(gtk_builder_get_object(builder, "add_blanches"));
   
   GtkWidget *add_noires;
   add_noires = GTK_WIDGET(gtk_builder_get_object(builder, "add_noires"));

   GtkWidget *add_croche;
   add_croche = GTK_WIDGET(gtk_builder_get_object(builder, "add_croche"));

   GtkWidget *add_4;
   add_4 = GTK_WIDGET(gtk_builder_get_object(builder, "add_4"));


    // Connexions des signaux Glade
    gtk_builder_connect_signals(builder, NULL);

    // Connexions des signaux Glade boutons notes
    g_signal_connect(add_blanche, "clicked", G_CALLBACK(nom_de_la_fonction_callback), NULL);
    g_signal_connect(add_noires, "clicked", G_CALLBACK(nom_de_la_fonction_callback), NULL);
    g_signal_connect(add_croche, "clicked", G_CALLBACK(nom_de_la_fonction_callback), NULL);
    g_signal_connect(add_4, "clicked", G_CALLBACK(nom_de_la_fonction_callback), NULL);

    // Affichage de la fenêtre
    gtk_widget_show(window);

    // Boucle principale GTK+
    gtk_main();

    // ...

    return 0;
}




