#include "Editor/conv.h"

void file_selected(GtkFileChooserButton *button, gpointer user_data)
{
    // Récupérer le chemin absolu du fichier sélectionné
    const gchar *fullPath = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(button));
    const gchar* filename = g_path_get_basename(fullPath);
    g_print("Chemin du fichier sélectionné : %s\n", filename);
    conv(g_strdup(fullPath));
    
    GtkWidget *fixed = user_data;
    GtkWidget *window = gtk_widget_get_parent(fixed);
    GtkWidget *image = gtk_image_new_from_file("Editor/partition.png");
    gtk_container_add(GTK_CONTAINER(fixed), image);
    gtk_fixed_move(GTK_FIXED(fixed), GTK_WIDGET(image), 330, 250);
    gtk_widget_show_all(window);
    // Afficher le chemin du fichier sélectionné
    g_print("Chemin du fichier sélectionné : %s\n", filename);
}

