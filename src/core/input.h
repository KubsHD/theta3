#pragma once
#include <SDL.h>

struct Mouse
{
	bool LMB, RMB;
	float scroll;
	int x, y;
};

class Input
{
public:
	bool key_down(SDL_Scancode scanCode);
	bool key_held(SDL_Scancode scanCode);

	void init();
	void update(SDL_Event& evt);
};



