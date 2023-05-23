#include <gtk/gtk.h>
#include <gst/gst.h>
#include "record.h"

GstElement *pipeline;
GstElement *source;
GstElement *encoder;
GstElement *sink;

void rec(GtkWidget *button, gpointer data)
{
    GdkRGBA color;
    gdk_rgba_parse(&color, "red");
    gtk_widget_override_background_color(button, GTK_STATE_FLAG_NORMAL, &color);
    gst_element_set_state(pipeline, GST_STATE_NULL);

    // Spécifiez le nom de fichier de sortie pour l'enregistrement
    const gchar *filename = "enregistrement.wav";

    // Configurez l'élément sink pour enregistrer dans un fichier
    g_object_set(G_OBJECT(sink), "location", filename, NULL);

    // Démarrez le pipeline
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    g_print("RECORDING...\n");
}

void arreterEnregistrement(GtkButton *button, gpointer data)
{
    // Arrêtez le pipeline
    gst_element_set_state(pipeline, GST_STATE_NULL);
    g_print("STOP RECORD\n");

}
