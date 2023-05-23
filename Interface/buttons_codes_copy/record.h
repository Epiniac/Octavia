#ifndef RECORD_H
#define RECORD_H
#include <gtk/gtk.h>
#include <gst/gst.h>

extern GstElement *pipeline;
extern GstElement *source;
extern GstElement *encoder;
extern GstElement *sink;


void rec(GtkButton *button, gpointer data);
void arreterEnregistrement(GtkButton *button, gpointer data);



#endif


