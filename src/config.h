#include <stdio.h>
#include <assert.h>
#include <gtk/gtk.h>
#include <gconf/gconf-client.h>

static gboolean toggleCb(GtkWidget* widget, GdkEvent* event, gpointer data);
