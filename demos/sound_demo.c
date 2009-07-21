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


/* This is a callback function. The data arguments are ignored
 * in this example. More on callbacks below. */
static void check( GtkWidget *widget,
                   gpointer   data )
{
    
/* Use libcanbera to play an event sound and specify a visual effect to go along with it.*/
    printf("%d",ca_context_play (ca_gtk_context_get (), 0,
			 CA_PROP_EVENT_ID, "dialog-information",
			 CA_PROP_EVENT_DESCRIPTION, "Hi seaslug",
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
			 CA_PROP_EVENT_ID, "dialog-error",
			 CA_PROP_EVENT_DESCRIPTION, "colorcolorcolor",
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
static void save(GtkWidget *widget, gpointer window) {
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(window,
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "File saved.", "title");
  gtk_window_set_title(GTK_WINDOW(dialog), "Information");
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
static void toggle(GtkWidget *widget, gpointer data){
    g_print("asdasd toggle \n");
}

static void backspace(GtkWidget *widget, gpointer data){
    g_print("asdasd backspace \n");
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
    GtkWidget *buttonsave;
    GtkWidget *buttoncancel;
    GtkWidget *entry;
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
    buttonsave = gtk_button_new_with_label ("Save");
    buttoncancel = gtk_button_new_with_label("Cancel");
    entry = gtk_entry_new();

    
    /* When the button receives the "clicked" signal, it will call the
     * function hello() passing it NULL as its argument.  The hello()
     * function is defined above. */
 
    g_signal_connect (G_OBJECT (buttonsave), "clicked",
		      G_CALLBACK (check), NULL);
    g_signal_connect (G_OBJECT (buttoncancel), "clicked",
		      G_CALLBACK (error), NULL);
    //g_signal_connect(G_OBJECT(entry),"backspace",G_CALLBACK(error),NULL);
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
    gtk_box_pack_start(GTK_BOX(hbox), entry, TRUE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), buttonsave, TRUE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX(hbox), buttoncancel, TRUE, FALSE, 0);

    /* This packs the button into the window (a gtk container). */
    gtk_container_add (GTK_CONTAINER (window), hbox);

    
    /* The final step is to display this newly created widget. */
    gtk_widget_show (buttoncancel);
    gtk_widget_show (buttonsave);
    gtk_widget_show(entry);
    gtk_widget_show (hbox);
    
    /* and the window */
    gtk_widget_show (window);
    
    /* All GTK applications must have a gtk_main(). Control ends here
     * and waits for an event to occur (like a key press or
     * mouse event). */
    gtk_main ();
    
    return 0;
}
