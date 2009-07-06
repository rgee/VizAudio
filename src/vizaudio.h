#include <gtk/gtk.h>
#include <gdk/gdkscreen.h>
#include <cairo.h>

void flash_color();
void song_popup(char* artist, char* title);
void flash_image(char* filename);
void flash_text(char* text);
void print_text();

static gboolean endFlash(GtkWidget *window);

static void screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer user_data);
static gboolean time_handler (GtkWidget *widget);
static gboolean textDisplay(GtkWidget *widget, GdkEventExpose *event, gpointer user_data);

int isVAEnabled();
void initGConfFlag();
