#include <SDL.h>
#include <iostream>

class Window {
public:
	int x, y, w, h;
	bool fullscreen;
	bool quit;
	SDL_Window* pWindow;
	SDL_Surface* pSurface;

	void setDefault();
	void create();
	void close();
};