#include <gtk/gtk.h>
#include <gdk/gdkscreen.h>
#include <cairo.h>

void vizaudio_display(int id, char[] label = NULL);

static gboolean endFlash(GtkWidget *window);

static void screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer user_data);
static gboolean expose(GtkWidget *widget, GdkEventExpose *event, gpointer user_data);
static gboolean time_handler (GtkWidget *widget);
static gboolean textDisplay (GtkWidget *widget, GdkEventExpose *event, gpointer user_data);
