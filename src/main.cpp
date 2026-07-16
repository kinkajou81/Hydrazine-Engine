#include <stdio.h>

#include <string>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

void entry_point(void);

void kill(void) {
	SDL_EnableScreenSaver();
	SDL_Quit();
}

bool init(void) {
	if(!((bool)atexit(kill))) {
		printf("ERROR: atexit() Failed");
		exit(-1);
	}
	
	if(!SDL_Init(SDL_INIT_VIDEO)) {
		printf("ERROR: SDL Failed to Initialise: %s\n", SDL_GetError());
		exit(-1);
	}
	if(!SDL_DisableScreenSaver()) {
		printf("WARNING: Screensaver Failed to Turn off: %s\n", SDL_GetError());
	}
}

int main(int argc, char *argv[]) {
	init();

	entry_point();
	
	return 0;
}
