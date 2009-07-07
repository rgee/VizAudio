#include "canberra.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    
    out = (char*) ca_proplist_gets_unlocked(p, CA_PROP_MEDIA_FILENAME);
    
    printf("%s",out);
    
    printf("\n");
    
    return 0;
}
