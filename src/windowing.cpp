#include <stdint.h>

#include <string>
#include <chrono>
#include <thread>

#include <types.hpp>

namespace win {
	window_t windows[8] = {};
	std::string titles[8] = {};
	uint16_t dimensions[16] = {};
	window_properties properties[8] = {};
	bool update_properities[8] = {};
}

// -1 == failure; 0 == success; 1 == previously started
int main_window_start(const char* title, int16_t w, int16_t h, window_properties properties) {
	if(win::windows[0] != NULL) {
		printf("WARNING: Main Window Already Created");
		return 1;
	}

	win::properties[0] = properties;
	win::dimensions[0] = w;
	win::dimensions[1] = h;
	
	SDL_WindowFlags sdl_flags = (uint64_t)(((properties.fullscreen)?SDL_WINDOW_FULLSCREEN:0)|
				 ((properties.resizable)?SDL_WINDOW_RESIZABLE:0)|
				 ((properties.minimized)?SDL_WINDOW_MINIMIZED:0)|
				 ((properties.maximized)?SDL_WINDOW_MAXIMIZED:0)|
				 ((properties.grab_mouse)?SDL_WINDOW_MOUSE_GRABBED:0)|
				 SDL_WINDOW_INPUT_FOCUS|
				 SDL_WINDOW_MOUSE_FOCUS|
				 SDL_WINDOW_VULKAN);
	win::windows[0] = SDL_CreateWindow(title, w, h, sdl_flags);

	main_window_loop();
}

// only call from the thread that started the window
inline bool update_window(uint8_t window_number) {
	bool x;
	uint8_t error = 0;
	if(x = !SDL_SetWindowFullscreen(win::windows[window_number], win::properties[window_number].fullscreen)) {printf("WARNING: Property Fullscreen of Main Window Failed To Be Set: %s\n", SDL_GetError()); error += (uint8_t)x;}
	if(x = !SDL_SetWindowResizable(win::windows[window_number], win::properties[window_number].resizable)) {printf("WARNING: Property  Resizable of Main Window Failed To Be Set: %s\n", SDL_GetError()); error += (uint8_t)x;}
	if(win::properties[0].maximized) if(x = !SDL_MaximizeWindow(win::windows[window_number])) {printf("WARNING: Property Maximised of Main Window Failed To Be Set: %s\n", SDL_GetError()); error += (uint8_t)x;}
	if(!win::properties[0].maximized) if(x = !SDL_MinimizeWindow(win::windows[window_number])) {printf("WARNING: Property Maximised of Main Window Failed To Be Set: %s\n", SDL_GetError()); error += (uint8_t)x;}
	if(x = !SDL_SetWindowSurfaceVSync(win::windows[window_number], win::properties[window_number].vsync)) {printf("WARNING: Property VSYNC of Main Window Failed To Be Set: %s\n", SDL_GetError()); error += (uint8_t)x;}
	if(x != 0) return false;
}

static int main_window_loop() {
	while(true) {
		if(!SDL_UpdateWindowSurface(win::windows[0])) printf("WARNING: window failed to update %s\n", SDL_GetError());
		if(false) {
			update_window(0);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds());
	}

	SDL_DestroyWindow(win::windows[0]);
	win::windows[0] = NULL;
}
