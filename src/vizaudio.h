/**
* Project: VizAudio
* File name: vizaudio.h
* Description: This is the header file for the main VizAudio engine. 
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
#include <gdk/gdkscreen.h>
#include <cairo.h>
#include <gconf/gconf-client.h>

/* Visual Effects */
void flash_color();
void flash_image(char* filename);
void flash_text(char* text);

/* Visual Effect Helpers */
gboolean endFlash(GtkWidget *window);
void screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer user_data);
gboolean time_handler (GtkWidget *widget);
gboolean textDisplay(GtkWidget *widget, GdkEventExpose *event, gpointer user_data);

/* Utility Functions */
int isVAEnabled();
void initGConfFlag();
