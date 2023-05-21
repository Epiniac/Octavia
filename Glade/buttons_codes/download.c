void download_button(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *window = gtk_widget_get_ancestor(widget, GTK_TYPE_WINDOW);
    if (window != NULL) {
        GdkWindow *gdk_window = gtk_widget_get_window(window);
        GdkPixbuf *screenshot = gdk_pixbuf_get_from_window(gdk_window, 360, 320, 600,640);
        gdk_pixbuf_save(screenshot, "final.png", "png", NULL, NULL);
        g_object_unref(screenshot);
	g_print("DOWNLOAD!\n");
    }
}

