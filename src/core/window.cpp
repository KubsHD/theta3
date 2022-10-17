#include "window.h"

void Window::setDefault()
{
	// Initialize and set window variables to default values
	quit = false;
	x = 0;
	y = 0;
	w = 640;
	h = 480;
}

void Window::create()
{
	// Create window and get its surface
	pWindow = SDL_CreateWindow("Ozon", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		w, h, SDL_WINDOW_SHOWN);

	if (pWindow == NULL)
	{
		std::cout << "pWindow is NULL!" << std::endl;
	}
	pSurface = SDL_GetWindowSurface(pWindow);
}

void Window::close()
{
	// Clear surface and window pointers, close SLD.
	SDL_FreeSurface(pSurface);
	pSurface = NULL;
	SDL_DestroyWindow(pWindow);
	pWindow = NULL;
	SDL_Quit();
}

void Window::update()
{

}

