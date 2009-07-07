#include "canberra.h"
#include "vizaudio_hook.h"
#include "vizaudio.h"
#include "config.h"
#include "proplist.h"


#include <stdio.h>
#include <string.h>

void vizaudio_display(ca_proplist *proplist) {
	// Sorry for the goto. We skip the entire procedure if we're not enabled

	if(!isVAEnabled()){
		 goto finish;
	}
	
	char* effect;
	// Get the visual effect
    effect = (char*) ca_proplist_gets_unlocked(proplist, CA_PROP_EVENT_VISUAL_EFFECT);
	printf("NOT SEGFAULTING");
	if(!strcmp(effect, "SONG_INFO_POPUP")){
		// Grab additional info and goto finish if any are found
		char* artist;
		char* title;
		artist = (char*) ca_proplist_gets_unlocked(proplist, CA_PROP_MEDIA_ARTIST);
		title = (char*) ca_proplist_gets_unlocked(proplist, CA_PROP_MEDIA_TITLE);
		
		// Check for errors, break out if found
		if(!artist){
			printf("Artist not defined in property list\n");
			goto finish;
		}else if(!title){
			printf("Title not defined in property list\n");
			goto finish;
		}
		song_popup(artist, title);
	}
	else if (!strcmp(effect, "COLOR_ALERT")){
		flash_color();
		goto finish;
	}
	else if (!strcmp(effect, "IMAGE_ALERT")){
		char* filename = (char*) ca_proplist_gets_unlocked(proplist, CA_PROP_MEDIA_IMAGE_FILENAME);
		
		// Determine if the file actually exists
		FILE* file = fopen(filename, "r");
		if(!file){
			fclose(file);
		}else{
			printf("CA_PROP_MEDIA_IMAGE_FILENAME is invalid.\n");
			goto finish;
		}
		flash_image(filename);
	}
	else if(!strcmp(effect, "FLYING_DESCRIPTION_TEXT_ALERT")){
		char* text = (char*) ca_proplist_gets_unlocked(proplist, CA_PROP_EVENT_DESCRIPTION);
		
		// Check for errors
		if(!text){
			printf("CA_PROP_EVENT_DESCRIPTION is not defined.\n");
		}else{
			flash_text(text);
		}
	}
	
	finish:;
	// Do nothing. This point is reached when the function completes either
	// having displayed error messages or completing successfully.
}

