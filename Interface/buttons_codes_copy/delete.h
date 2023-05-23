#ifndef DELETE_H
#define DELETE_H
#include <gtk/gtk.h>


extern GtkWidget *add_blanches;
extern GtkWidget *add_noires;
extern GtkWidget *add_croche;
extern GtkWidget *add_4;

gboolean activate_delete(GtkWidget *widget, GdkEventButton *event, gpointer user_data);
gboolean on_image_button_press(GtkWidget *widget, GdkEventButton *event, gpointer user_data);
void load_image(GtkButton *widget, gpointer user_data);
gboolean print_image(GtkWidget *widget, GdkEventButton *event, gpointer user_data);
#endif


