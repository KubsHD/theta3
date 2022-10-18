#pragma once
#include <SDL.h>

class Mouse
{
public:
	bool LMB, RMB;
	float scroll;
	int x, y;
};

class Keyboard
{
public:
	bool KEY[322];


	bool update(SDL_Event evt);
};



