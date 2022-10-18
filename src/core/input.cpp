#include "input.h"

#include <SDL.h>
#include <iostream>

bool quit;




bool Keyboard::update(SDL_Event evt)
{
	quit = false;
	switch (evt.type)
	{
	case SDL_KEYDOWN:
		switch (evt.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			quit = true;
			break;
		case SDLK_w:
			std::cout << "pressed w\n";
			break;
		case SDLK_a:
			std::cout << "pressed a\n";
			break;
		case SDLK_s:
			std::cout << "pressed s\n";
			break;
		case SDLK_d:
			std::cout << "pressed d\n";	
			break;
		}
		
		
	case SDL_QUIT:
		quit = true;
		break;
	case SDL_CONTROLLERDEVICEADDED:
		//input_notify_pad_added();
		break;
	case SDL_CONTROLLERDEVICEREMOVED:
		//input_notify_pad_removed();
		break;
	}

	return quit;
}