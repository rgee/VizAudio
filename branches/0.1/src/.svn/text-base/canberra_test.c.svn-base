#include <canberra.h>
#include <stdlib.h>
#include <stdio.h>
/* Implementation of the callback function to use when a sound has completed
 * successfully.
 */
void callback_function(ca_context *c, uint32_t id ,int error_code, void *userdata){

	printf("error code:%d\n id:%d\n",error_code,id);
}

int main() {

	ca_context *c = NULL;
	ca_finish_callback_t callback = callback_function;
	/* Create a context for the event sounds for your application */
	ca_context_create(&c);

	/* Set a few application-global properties */
	ca_context_change_props(c,
	                        CA_PROP_APPLICATION_NAME, "An example",
				CA_PROP_APPLICATION_ID, "org.freedesktop.libcanberra.Test",
				CA_PROP_APPLICATION_ICON_NAME, "libcanberra-test",
			        NULL);

	// Create a proplist
	struct ca_proplist **props;

	if(ca_proplist_create(props)==0){
		printf("ca_proplist created successfully.\n");
	}
	else
		printf("ca_proplist not created successfully.\n");

	// Set some stuff in the list of properties to play the "button-pressed" sound
    ca_proplist_sets(*props,CA_PROP_EVENT_ID,"button-pressed");

	/* Um.. yeah, how else can I do this? */
    int bla = 0;
    int *userdata=&bla;
    ca_context_play_full(c,0,*props,callback,userdata);

	ca_context_destroy(c);
}
