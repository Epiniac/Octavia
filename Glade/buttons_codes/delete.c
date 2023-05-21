#include <gtk/gtk.h>

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

int main(int argc, char *argv[])
{
    // Initialisation de GTK                                                                                                                                                          
    gtk_init(&argc, &argv);

    // Chargement de l'interface Glade                                                                                                                                                
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "../editor.glade", NULL);

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    GtkWidget *delete_button = GTK_WIDGET(gtk_builder_get_object(builder, "delete_button"));
    GtkWidget *box1 = GTK_WIDGET(gtk_builder_get_object(builder, "box1"));
    GtkWidget *box2 = GTK_WIDGET(gtk_builder_get_object(builder, "box2"));
    GtkWidget *box3 = GTK_WIDGET(gtk_builder_get_object(builder, "box3"));
    GtkWidget *box4 = GTK_WIDGET(gtk_builder_get_object(builder, "box4"));

     

    // Enregistrement des fonctions de rappel pour les événements de clic et de déplacement de la souris                                                                             
    g_signal_connect(delete_button, "clicked", G_CALLBACK(activate_delete),FALSE);
    g_signal_connect(box1, "button-press-event", G_CALLBACK(on_image_button_press), NULL);
    g_signal_connect(box2, "button-press-event", G_CALLBACK(on_image_button_press), NULL);
    g_signal_connect(box3, "button-press-event", G_CALLBACK(on_image_button_press), NULL);
    g_signal_connect(box4, "button-press-event", G_CALLBACK(on_image_button_press), NULL);


    //g_signal_connect(image, "motion-notify-event", G_CALLBACK(on_image_motion_notify), builder);
                                                                                                                                                                           

    // Lancement de la boucle principale de GTK                                                                                                                                       
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

