gboolean isButtonActivated = FALSE;
gboolean load = FALSE;
GtkWidget *event_box1 = NULL;

GtkWidget *add_blanches;
GtkWidget *add_noires;
GtkWidget *add_croche;
GtkWidget *add_4;

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

void load_image(GtkButton *widget, gpointer user_data)
{
	GtkWidget *fixed = user_data;
	GtkWidget *window = gtk_widget_get_parent(fixed);
	event_box1 = gtk_event_box_new();

	if(widget == GTK_BUTTON(add_blanches))
	{

		GtkWidget *blanche = gtk_image_new_from_file("../images/images_notes/note_blanche.png");
		gtk_container_add(GTK_CONTAINER(event_box1), blanche);
	}
	else if (widget == GTK_BUTTON(add_noires))
	{


		GtkWidget *noire = gtk_image_new_from_file("../images/images_notes/note_noires.png");
		gtk_container_add(GTK_CONTAINER(event_box1),noire);
	}
	else if(widget == GTK_BUTTON(add_croche))
	{

		GtkWidget *croche = gtk_image_new_from_file("../images/images_notes/note_croche.png");
		gtk_container_add(GTK_CONTAINER(event_box1),croche);
	}
	else if (widget == GTK_BUTTON(add_4))
	{

		GtkWidget *croches = gtk_image_new_from_file("../images/images_notes/note_croches.png");
		gtk_container_add(GTK_CONTAINER(event_box1),croches);
	}



    //gtk_container_add(GTK_CONTAINER(fixed), event_box);                                                                                                                             
    //gtk_fixed_move(GTK_FIXED(fixed), GTK_WIDGET(image), 330, 250);                                                                                                                  
    //gtk_widget_show_all(window);                                                                                                                                                    
    load = TRUE;
    //event = event_box;                                                                                                                                                              
    g_signal_connect(event_box1, "button-press-event", G_CALLBACK(on_image_button_press), NULL);
    g_print("LOAD!\n");


}

// Fonction de rappel pour l'événement "button-press-event" de la fenêtre                                                                                                             
gboolean print_image(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{
  if (load)
    {
  // Vérifier si le bouton de la souris est le bouton gauche (button 1)                                                                                                               
    if (event->button == 1)
      {
        // Récupérer les coordonnées x et y du clic de la souris                                                                                                                      
        gdouble x = event->x;
        gdouble y = event->y;

        //GtkWidget *event_box = event;                                                                                                                                               
        GtkWidget *fixed = user_data;
        GtkWidget *glade_widget = GTK_WIDGET(user_data);
        gint glade_x, glade_y;
        gtk_widget_translate_coordinates(glade_widget, widget, x, y, &glade_x, &glade_y);

        // Afficher les coordonnées relatives à l'interface Glade                                                                                                                     
        g_print("Position dans l'interface Glade : x = %d, y = %d\n", glade_x, glade_y);

        // Afficher les coordonnées de la souris                                                                                                                                      
        //g_print("Position de la souris : x = %f, y = %f\n", x, y);
        	gtk_fixed_put(GTK_FIXED(fixed), event_box1, glade_x,glade_y);
        	gtk_widget_show_all(widget);
        	load = FALSE;
	
	}
    } 
}
