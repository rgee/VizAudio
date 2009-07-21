/**
* Project: VizAudio
* File name: color_flash.c
* Description: This is simply a test program for visual effects
* 
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author       Ryan Gee
* @author       Rachel Foecking
* @author		Foster Nichols
* @copyright    Humanitarian FOSS Project (http://www.hfoss.org), Copyright (C) 2009.
* @package
* @subpackage
* @tutorial
* @license  http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
* @version
*/

#include <gtk/gtk.h>
#include <canberra.h>
#include <canberra-gtk.h>

/* Destroys the window. Wrapped to facilitate timing from
 * g_timeout_add() */
static gboolean endFlash(GtkWidget *window){
    gtk_object_destroy(GTK_OBJECT(window));
    return FALSE;
}

/* This is a callback function. The data arguments are ignored
 * in this example. More on callbacks below. */
static void color( GtkWidget *widget,
                   gpointer   data )
{
    
/* Use libcanbera to play an event sound and specify a visual effect to go along with it.*/
    g_print ("Flash a color!\n");
    printf("%d",ca_context_play (ca_gtk_context_get (), 0,
			 CA_PROP_EVENT_ID, "button-pressed",
			 CA_PROP_EVENT_DESCRIPTION, "colorcolorcolor",
             CA_PROP_VISUAL_EFFECT, "COLOR_ALERT",
             CA_PROP_COLOR, "blue",
            NULL));
}

/* This is a callback function. The data arguments are ignored
 * in this example. More on callbacks below. */
static void text( GtkWidget *widget,
                   gpointer   data )
{
    
/* Use libcanbera to play an event sound and specify a visual effect to go along with it.*/
    g_print ("Display some text!\n");
    printf("%d",ca_context_play (ca_gtk_context_get (), 0,
			 CA_PROP_EVENT_ID, "button-pressed",
			 CA_PROP_EVENT_DESCRIPTION, "This text will alert you!",
             CA_PROP_VISUAL_EFFECT, "FLYING_DESCRIPTION_TEXT_ALERT",
            NULL));

}

/* This is a callback function. The data arguments are ignored
 * in this example. More on callbacks below. */
static void image( GtkWidget *widget,
                   gpointer   data )
{
    
/* Use libcanbera to play an event sound and specify a visual effect to go along with it.*/
    g_print ("It's a seaslug!\n");
    printf("%d",ca_context_play (ca_gtk_context_get (), 0,
			 CA_PROP_EVENT_ID, "button-pressed",
			 CA_PROP_EVENT_DESCRIPTION, "Hi seaslug",
             CA_PROP_VISUAL_EFFECT, "IMAGE_ALERT",
             CA_PROP_MEDIA_IMAGE_PATH, "/home/rfoeckin/apps/images/seaslug.GIF",
            NULL));
}

/* Destroys the window. Wrapped to facilitate timing from
 * g_timeout_add() */
static gboolean destroy_error_window(GtkWidget *window){
    gtk_object_destroy(GTK_OBJECT(window));
    return FALSE;
}

static void error(GtkWidget *widget, gpointer window){
  /* Play an alert sound/visual event */
  printf("%d",ca_context_play (ca_gtk_context_get (), 0,
			 CA_PROP_EVENT_ID, "button-pressed",
			 CA_PROP_EVENT_DESCRIPTION, "colorcolorcolor",
             CA_PROP_VISUAL_EFFECT, "COLOR_ALERT",
             CA_PROP_COLOR, "red",
            NULL));
  /* Set up and display an error dialog */
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(window,
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
           "An error has occurred.  Please do not be alarmed.");
  gtk_window_set_title(GTK_WINDOW(dialog), "Error");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
  
}
static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    /* If you return FALSE in the "delete_event" signal handler,
     * GTK will emit the "destroy" signal. Returning TRUE means
     * you don't want the window to be destroyed.
     * This is useful for popping up 'are you sure you want to quit?'
     * type dialogs. */

    g_print ("delete event occurred\n");
   
    /* Change TRUE to FALSE and the main window will be destroyed with
     * a "delete_event". */

    return FALSE;
}

/* Another callback */
static void destroy( GtkWidget *widget,
                     gpointer   data )
{
    gtk_main_quit ();
}

int main( int   argc,
          char *argv[] )
{
    /* GtkWidget is the storage type for widgets */
    GtkWidget *window;
    GtkWidget *buttoncolor;
    GtkWidget *buttontext;
    GtkWidget *buttonimage;
    GtkWidget *buttonerror;
    GtkWidget *hbox;
    
    /* This is called in all GTK applications. Arguments are parsed
     * from the command line and are returned to the application. */
    gtk_init (&argc, &argv);
    
    /* create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
    /* When the window is given the "delete_event" signal (this is given
     * by the window manager, usually by the "close" option, or on the
     * titlebar), we ask it to call the delete_event () function
     * as defined above. The data passed to the callback
     * function is NULL and is ignored in the callback function. */
    g_signal_connect (G_OBJECT (window), "delete_event",
		      G_CALLBACK (delete_event), NULL);
    
    /* Here we connect the "destroy" event to a signal handler.  
     * This event occurs when we call gtk_widget_destroy() on the window,
     * or if we return FALSE in the "delete_event" callback. */
    g_signal_connect (G_OBJECT (window), "destroy",
		      G_CALLBACK (destroy), NULL);
    
    /* Sets the border width of the window. */
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    
    /* Creates a new button with the label "Hello World". */
    buttoncolor = gtk_button_new_with_label ("Flash color");
    buttontext = gtk_button_new_with_label ("Flash text");
    buttonimage = gtk_button_new_with_label ("Flash image");
    buttonerror = gtk_button_new_with_label("Error");
    
    /* When the button receives the "clicked" signal, it will call the
     * function hello() passing it NULL as its argument.  The hello()
     * function is defined above. */
    g_signal_connect (G_OBJECT (buttoncolor), "clicked",
		      G_CALLBACK (color), NULL);
    g_signal_connect (G_OBJECT (buttontext), "clicked",
		      G_CALLBACK (text), NULL);
    g_signal_connect (G_OBJECT (buttonimage), "clicked",
		      G_CALLBACK (image), NULL);
    g_signal_connect(G_OBJECT(buttonerror), "clicked", G_CALLBACK (error), NULL);
    
    /* This will cause the window to be destroyed by calling
     * gtk_widget_destroy(window) when "clicked".  Again, the destroy
     * signal could come from here, or the window manager. */
    

    /*g_signal_connect_swapped (G_OBJECT (button), "clicked",
			      G_CALLBACK (gtk_widget_destroy),
                              G_OBJECT (window));*/  
    hbox = gtk_hbox_new (FALSE, 0);
    
    /* Pack the button into the quitbox.
     * The last 3 arguments to gtk_box_pack_start are:
     * expand, fill, padding. */
    gtk_box_pack_start (GTK_BOX (hbox), buttoncolor, TRUE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), buttontext, TRUE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), buttonimage, TRUE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX(hbox), buttonerror, TRUE, FALSE, 0);


    /* This packs the button into the window (a gtk container). */
    gtk_container_add (GTK_CONTAINER (window), hbox);

    
    /* The final step is to display this newly created widget. */
    gtk_widget_show (buttoncolor);
    gtk_widget_show (buttontext);
    gtk_widget_show (buttonimage);
    gtk_widget_show (buttonerror);
    gtk_widget_show (hbox);
    
    /* and the window */
    gtk_widget_show (window);
    
    /* All GTK applications must have a gtk_main(). Control ends here
     * and waits for an event to occur (like a key press or
     * mouse event). */
    gtk_main ();
    
    return 0;
}
