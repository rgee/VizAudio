/**
 * A small app to allow users to simply change VizAudio configurations.
 */

#include <stdio.h>
#include <assert.h>
#include <gtk/gtk.h>
#include <gconf/gconf-client.h>


/* Global variables */
GConfClient* client;
gchar* dir = "/apps/vizaudio/preferences";
gchar* key = "/apps/vizaudio/preferences/enabled";

static gboolean toggleCb(GtkWidget* widget, GdkEvent* event, gpointer data)
{
    if(gtk_toggle_button_get_active(widget)){
        gconf_client_set_int(client, key, 0, NULL);
    }
    else
    {
        gconf_client_set_int(client, key, 1, NULL);
    }
}

int main(int argc, char *argv[])
{
    GtkWidget* window;
    GtkWidget* toggleButton;
    GtkWidget* quitButton;
    GtkWidget* vBox;
    
    client = gconf_client_get_default();
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    toggleButton = gtk_toggle_button_new_with_label("Enable VizAudio");
    
    quitButton = gtk_button_new_with_label("GTK_STOCK_QUIT");
    gtk_button_set_use_stock(GTK_BUTTON(quitButton), TRUE);
    
    vBox = gtk_vbox_new(TRUE, 1);
    
    gtk_box_pack_start(GTK_BOX(vBox), toggleButton, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vBox), quitButton, FALSE, FALSE, 0);
    
    gtk_container_add(GTK_CONTAINER(window), vBox);

    assert(gconf_client_dir_exists(client, dir, NULL));

    if(gconf_client_get_int(client, key, NULL))
    {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggleButton), TRUE);
    }
    else
    {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggleButton), FALSE);
    }

    g_signal_connect(G_OBJECT(toggleButton), "toggled",
                    G_CALLBACK(toggleCb), NULL);
    
    gtk_widget_show(vBox);
    gtk_widget_show(window);
    
    gtk_main();
}


