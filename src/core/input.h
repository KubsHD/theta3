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
	bool GetKeyDown(SDL_Scancode scanCode);

	void Init();
	bool Update(SDL_Event& evt);
};



