void new_partition(GtkButton *button, gpointer user_data)
{
  GtkImage *image = user_data;
   // Associer un chemin à la GtkImage                                                                                                                                               
    const gchar *chemin_image = "../images/empty.jpg";
    gtk_image_set_from_file(GTK_IMAGE(image), chemin_image);

}

