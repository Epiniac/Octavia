#include "new.h"

void new_partition(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *fixed = user_data;
    GtkWidget *window = gtk_widget_get_parent(fixed);                                                                                                 
    GtkWidget *image = gtk_image_new_from_file("../images/empty.jpg");
    gtk_container_add(GTK_CONTAINER(fixed), image);
    gtk_fixed_move(GTK_FIXED(fixed), GTK_WIDGET(image), 330, 250);
    gtk_widget_show_all(window);
}

