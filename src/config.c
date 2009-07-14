/**
* Project: VizAudio
* File name: config.c
* Description: A small application to allow users to change VizAudio configurations
* easily.
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

#include "config.h"


/* Global variables */
GConfClient* client;
gchar* dir = "/apps/vizaudio/preferences";
gchar* key = "/apps/vizaudio/preferences/enabled";

static gboolean toggleCb(GtkWidget* widget, GdkEvent* event, gpointer data)
{
    /* Link the toggle button to the Gconf variable */
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)))
    {
        gconf_client_set_int(client, "/apps/vizaudio/preferences/enabled", 1, NULL);
    }
    else
    {
        gconf_client_set_int(client, "/apps/vizaudio/preferences/enabled", 0, NULL);
    }
    return FALSE;
}

static gboolean delete_event(GtkWidget* widget, GdkEvent* event, gpointer data)
{
    gtk_main_quit();
    return FALSE;
}

int main(int argc, char *argv[])
{
    gtk_init(NULL, NULL);
    GtkWidget* window;
    GtkWidget* toggleButton;
    GtkWidget* quitButton;
    GtkWidget* vBox;
    
    client = gconf_client_get_default();
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "VizAudio Configuration Manager");
    
    toggleButton = gtk_toggle_button_new_with_label("Enable VizAudio");
    
    quitButton = gtk_button_new_from_stock(GTK_STOCK_QUIT);
    gtk_button_set_use_stock(GTK_BUTTON(quitButton), TRUE);
    
    vBox = gtk_vbox_new(TRUE, 8);
    gtk_box_pack_start(GTK_BOX(vBox), toggleButton, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vBox), quitButton, FALSE, FALSE, 0);
    

    assert(gconf_client_dir_exists(client, dir, NULL));

    /* Set the inital toggle button state */
    if(gconf_client_get_int(client, "/apps/vizaudio/preferences/enabled", NULL))
    {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggleButton), TRUE);
    }
    else
    {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggleButton), FALSE);
    }

    /* Link up our callbacks */
    g_signal_connect(G_OBJECT(toggleButton), "toggled",
                    G_CALLBACK(toggleCb), NULL);
                    
    g_signal_connect(G_OBJECT(window), "delete_event",
                    G_CALLBACK(delete_event), NULL);
                    
    g_signal_connect_swapped(G_OBJECT(quitButton), "clicked",
                            G_CALLBACK(gtk_main_quit), G_OBJECT(window));
    
    
    gtk_container_add(GTK_CONTAINER(window), vBox);
    
    gtk_widget_show(quitButton);
    gtk_widget_show(toggleButton);
    gtk_widget_show(vBox);
    gtk_widget_show(window);
    
    gtk_main();
    
    return 0;
}


