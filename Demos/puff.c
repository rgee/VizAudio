#include <cairo.h>
#include <gtk/gtk.h>
#include <gdk/gdkscreen.h>


gboolean timer = TRUE;
static void screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer user_data);

static gboolean
on_expose_event(GtkWidget *widget,
    GdkEventExpose *event,
    gpointer data)
{
  cairo_t *cr;
  cairo_text_extents_t extents;

  static gdouble alpha = 1.0;
  static gdouble size = 1;
  cr = gdk_cairo_create(widget->window);

  cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 0.0); 

  gint x = widget->allocation.width / 2;
  gint y = widget->allocation.height / 2;
    cairo_set_operator (cr, CAIRO_OPERATOR_SOURCE);

  cairo_paint(cr);

  cairo_select_font_face(cr, "Courier",
      CAIRO_FONT_SLANT_NORMAL,
      CAIRO_FONT_WEIGHT_BOLD);

  size += 0.8;

  if (size > 20) {
      alpha -= 0.01;
  }

  cairo_set_font_size(cr, size);

  cairo_set_source_rgb(cr, 0.5, 0, 0); 

  cairo_text_extents(cr, "SEASLUGS", &extents);
  cairo_move_to(cr, x - extents.width/2, y);
  cairo_text_path(cr, "SEASLUGS");
  cairo_clip(cr);
  cairo_stroke(cr);
  cairo_paint_with_alpha(cr, alpha);

  if (alpha <= 0) {
      timer = FALSE;
  }

  cairo_destroy(cr);

  return FALSE;
}

static gboolean
time_handler (GtkWidget *widget)
{
  if (widget->window == NULL) return FALSE;

  if (!timer) return FALSE;

  gtk_widget_queue_draw(widget);

  return TRUE;
}

gboolean supports_alpha = FALSE;
static void screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer userdata)
{
    /* To check if the display supports alpha channels, get the colormap */
    GdkScreen *screen = gtk_widget_get_screen(widget);
    GdkColormap *colormap = gdk_screen_get_rgba_colormap(screen);

    if (!colormap)
    {
        printf("Your screen does not support alpha channels!\n");
        colormap = gdk_screen_get_rgb_colormap(screen);
        supports_alpha = FALSE;
    }
    else
    {
        printf("Your screen supports alpha channels!\n");
	printf("All visual effects will be drawn without transparency.\n");
        supports_alpha = TRUE;
    }

    /* Now we have a colormap appropriate for the screen, use it */
    gtk_widget_set_colormap(widget, colormap);
}

int main (int argc, char *argv[])
{
  GtkWidget *window;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  g_signal_connect(window, "expose-event",
      G_CALLBACK(on_expose_event), NULL);
	
  g_signal_connect(G_OBJECT(window), "screen-changed",
	G_CALLBACK(screen_changed), NULL);
	
  g_signal_connect(window, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 500, 200); 
  gtk_window_set_title(GTK_WINDOW(window), "puff");
  gtk_widget_set_app_paintable(window, TRUE);
  gtk_window_set_decorated(GTK_WINDOW(window), FALSE);

  screen_changed(window, NULL, NULL);
  g_timeout_add(14, (GSourceFunc) time_handler, (gpointer) window);
  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
