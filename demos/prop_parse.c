/**
* Project: VizAudio
* File name: prop_parse.c
* Description: This is simply a test program for libcanberra property lists
* and GConf support.
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


#include "canberra.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Test callback function. */
static void callback(ca_context *c, uint32_t id, int error, void *userdata) {
    fprintf(stderr, "callback called for id %u, error '%s', userdata=%p\n", id, ca_strerror(error), userdata);
}

int main(int argc, char *argv[]){
    ca_context *c;
    ca_proplist *p;
    int ret;
    
    char *out;

    ret = ca_context_create(&c);
    fprintf(stderr, "create: %s\n", ca_strerror(ret));
    ret = ca_context_change_props(c,
                                    CA_PROP_APPLICATION_NAME, "Example Application",
                                    CA_PROP_APPLICATION_ID,     "org.ryan.test",
                                    CA_PROP_WINDOW_X11_SCREEN, getenv("DISPLAY"),
                                    NULL);

    ret = ca_context_open(c);
    fprintf(stderr, "open: %s\n", ca_strerror(ret));
    
    ca_proplist_create(&p);
    ca_proplist_sets(p, CA_PROP_EVENT_ID, "desktop-login");
    ca_proplist_sets(p, CA_PROP_MEDIA_FILENAME, "/usr/share/sounds/uxknkurz.wav");
    ca_proplist_sets(p, CA_PROP_MEDIA_NAME, "New email recieved");
    ca_proplist_sets(p, CA_PROP_EVENT_VISUAL_EFFECT, "COLOR_ALERT");
    
	ret = ca_context_play_full(c, 1, p, callback, (void*) 0x4711);
    ca_proplist_destroy(p);
    fprintf(stderr, "play_full: %s\n", ca_strerror(ret));
    
    return 0;
}
