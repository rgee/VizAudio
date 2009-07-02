#include "canberra.h"
#include "vizaudio_hook.h"
#include "vizaudio.h"
#include <stdio.h>

void vizaudio_display(ca_proplist *proplist) {
    char *effect;
	
	// Get the visual effect
    effect = (char*) ca_proplist_gets_unlocked(proplist, CA_PROP_EVENT_VISUAL_EFFECT);
	
	switch(effect){
	case "SONG_INFO_POPUP":;
		// Grab additional info
		char* artist = (char*) ca_proplist_gets_unlocked(proplist, CA_PROP_MEDIA_ARTIST);
		char* title = (char*) ca_proplist_gets_unlocked(proplist, CA_PROP_MEDIA_TITLE);
		
		// Check for errors, break out if found
		if(!artist){
			printf("Artist not defined in property list\n");
			break;
		}else if(!title){
			printf("Title not defined in property list\n");
			break;
		}
		song_popup(artist, title);
		break;
	case "COLOR_ALERT":;
		flash_color();
		break;
	case "IMAGE_ALERT":;
		char* filename = (char*) ca_proplist_gets_unlock(proplist, CA_PROP_MEDIA_IMAGE_FILENAME);
		
		// Determine if the file actually exists
		if(FILE* file = fopen(filename, "r"))
		{
			fclose(file)
		}else{
			printf("CA_PROP_MEDIA_IMAGE_FILENAME is invalid.\n");
			break;
		}
		flash_image(filename);
	case "FLYING_DESCRIPTION_TEXT_ALERT":;
		char* text = (char*) ca_proplist_gets_unlock(proplist, CA_PROP_EVENT_DESCRIPTION);
		
		// Check for errors
		if(!text){
			printf("CA_PROP_EVENT_DESCRIPTION is not defined.\n");
		}else{
			flash_text(text);
		}
	}
}
