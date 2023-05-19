#include <stdio.h>
#include <SDL2/SDL.h>
#include <gtk/gtk.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtkx.h>

GtkBuilder *builder;
GtkWidget *window;
GtkWidget *add_blanches;
GtkWidget *add_noires;
GtkWidget *add_croche;
GtkWidget *add_4;


int main(int argc, char *argv[])
{
	gtk_init(&argc,&argv); //init GTK

//establish contact with xml code used to adjust widget settings

	builder = gtk_builder_new_from_file("editor.glade");
	
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

	gtk_builder_connect_signals(builder, NULL);

	add_blanches = GTK_WIDGET(gtk_builder_get_object(builder, "add_blanches"));
	add_noires = GTK_WIDGET(gtk_builder_get_object(builder,"add_noires"));
	add_croche = GTK_WIDGET(gtk_builder_get_object(builder,"add_croche"));
	add_4 = GTK_WIDGET(gtk_builder_get_object(builder,"add_4"));

	gtk_widget_show(window);
	gtk_main();
	
	return EXIT_SUCCESS;
}

void test_click(GtkButton *b)
{
	gtk_label_set_text(GTK_LABEL(add_blanches),(const gchar*) "Hello Wold");
}



