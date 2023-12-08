#include "window.h"
#include <utils/profiler.h>

Window::Window()
{
	// Initialize and set window variables to default values
	quit = false;
	x = 100;
	y = 100;
	w = 800;
	h = 450;
}

void Window::create()
{
	THETA_PROFILE;

	// Create window and get its surface
	pWindow = SDL_CreateWindow("theta3", x, y,
		w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (pWindow == NULL)
	{
		std::cout << "pWindow is NULL!" << std::endl;
	}
}

void Window::close()
{
	// Clear surface and window pointers, close SDL.
	SDL_DestroyWindow(pWindow);
}

void Window::getCurrentSize()
{
	// updating window dimensions
	SDL_GetWindowSize(pWindow, &w, &h);
	//std::cout << "w: " << w << "  |  h: " << h << std::endl;

}

