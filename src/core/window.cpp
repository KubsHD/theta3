#include "window.h"

Window::Window()
{
	// Initialize and set window variables to default values
	quit = false;
	x = 0;
	y = 0;
	w = 1600;
	h = 900;
}

void Window::create()
{
	// Create window and get its surface
	pWindow = SDL_CreateWindow("theta3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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

