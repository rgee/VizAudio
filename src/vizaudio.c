/* This is the main source file for VizAudio. Audio function calls will pass through 
 *  vizaudio_display, carrying the same information as is passed ca_context_play in
 *  libCanberra. This will allow us to select the proper visual effect based on the 
 *  libCanberra property list. (Proplist parsing not implemented ATM)
 */



#include <vizaudio.h>


/* Global Variables */
gboolean timer = TRUE;

//Quickly displays an image
void flash_image(char* filename) {

    GtkWidget *window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    
    GtkWidget* image;
    image = gtk_image_new_from_file(filename);
    gtk_container_add (GTK_CONTAINER (window), image);
    
    gtk_widget_show(image);    
    gtk_widget_show(window);        
    
    /* This function takes the function endFlash and calls it with a time
     * interval defined by the first parameter */
    g_timeout_add(250, (GSourceFunc)endFlash, (gpointer)window);
}

//Quickly displays a color fullscreen
void flash_color() {
    GtkWidget *window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
    gtk_window_fullscreen(GTK_WINDOW(window));

    GdkColor color;
    gdk_color_parse("light blue", &color);
    gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);
    
    
    gtk_widget_show(window);
    
/* This function takes the function endFlash and calls it with a time
 * interval defined by the first parameter 
 */
    g_timeout_add(250, (GSourceFunc)endFlash, (gpointer)window);
}

//Quickly zooms some text at you
void flash_text(char* text) {

    GtkWidget *window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Audio Event Alert!");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_widget_set_app_paintable(window, TRUE);
    gtk_window_set_default_size (GTK_WINDOW (window), 800, 600);
    
    /* Link the callbacks */
    g_signal_connect(G_OBJECT(window), "destroy", gtk_main_quit, NULL);
    g_signal_connect(G_OBJECT(window), "expose-event", G_CALLBACK(textDisplay), (gpointer)(text));
    g_signal_connect(G_OBJECT(window), "screen-changed", G_CALLBACK(screen_changed), NULL);
    
    gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
    
    screen_changed(window, NULL, NULL);
    
    g_timeout_add(14, (GSourceFunc) time_handler, (gpointer) window);
    gtk_widget_show(window);
}

void print_text() {
    printf("DEFAULT\n"); //never call this method
}

static gboolean endFlash(GtkWidget *window){
    gtk_object_destroy(GTK_OBJECT(window));
    return FALSE;
}

/* Callback function for whenever the GdkScreen becomes the active screen
 * for the passed widget 
 */
static void screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer user_data){
    /* To check if the display supports alpha channels, get the colormap */
    GdkScreen *screen = gtk_widget_get_screen(widget);
    GdkColormap *colormap = gdk_screen_get_rgba_colormap(screen);
    
    gtk_widget_set_colormap(widget, colormap);
}

static gboolean time_handler (GtkWidget *widget){
  if (widget->window == NULL) return FALSE;

  if (!timer) return FALSE;

    // Send expose events
  gtk_widget_queue_draw(widget);

  return TRUE;
}

/* This function displays text flying toward the screen, growing as it moves.
 *
 */
static gboolean textDisplay(GtkWidget *widget, GdkEventExpose *event, gpointer user_data) {
    cairo_t *cr;
    cairo_text_extents_t extents;   

    static gdouble alpha = 1.0;
    static gdouble size = 1;
    char* text = (char*) user_data;
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

    cairo_text_extents(cr, text, &extents);
    cairo_move_to(cr, x - extents.width/2, y);
    cairo_text_path(cr, text);
    cairo_clip(cr);
    cairo_stroke(cr);
    cairo_paint_with_alpha(cr, alpha);

    if (alpha <= 0) {
      timer = FALSE;
    }

    cairo_destroy(cr);
    //gtk_object_destroy(GTK_OBJECT(widget));
    return FALSE;
}
