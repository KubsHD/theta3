#pragma once
#include <SDL.h>

#include <glm/glm.hpp>
#include <core/types.h>

struct Mouse
{
	bool LMB, RMB;
	float scroll;
	glm::ivec2 pos;
	Uint32 buttons;
};

class Input
{
public:
	static bool key_down(SDL_Scancode scanCode);
	static bool key_held(SDL_Scancode scanCode);
	static SDL_MouseWheelEvent get_wheel();


	void init();
	void update(SDL_Event& evt);
	void update_mouse_wheel(SDL_MouseWheelEvent mevt);

	static bool mouse_down(int key);
	static bool mouse_held(int key);
	static Vec2 get_mouse_pos();
};



