gboolean isButtonActivated = FALSE;

static gboolean activate_delete(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{
   if (!isButtonActivated)
   {
        // Activate the button
        isButtonActivated = TRUE;
        g_print("Button activated\n");
   }
}


static gboolean on_image_button_press(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{
  if (isButtonActivated)
    {
      GtkWidget *picture = GTK_WIDGET(user_data);  // Cast the data pointer to GtkWidget                                                                                                \
                                                                                                                                                                                      

      // Get the parent container and remove the picture widget from it
      /*
    GtkWidget *parent = gtk_widget_get_parent(widget);
    gtk_container_remove(GTK_CONTAINER(parent), picture);
    gtk_container_remove(GTK_CONTAINER(parent), widget);
      */
    // Free the memory allocated for the picture widget                                                                                                                              

    gtk_widget_destroy(widget);
    isButtonActivated = FALSE;
    g_print("On clicked !!!!\n");
    }
}
