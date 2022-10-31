#include "input.h"

#include <SDL.h>
#include <iostream>

bool quit;

static Uint8* key_state;
static Uint8* last_key_state;

static SDL_GameController* pad;

static bool input_locked = false;


void Input::update(SDL_Event& evt)
{
	std::memcpy(last_key_state, key_state, sizeof(Uint32) * SDL_NUM_SCANCODES);
	std::memcpy(key_state, SDL_GetKeyboardState(NULL), sizeof(Uint32) * SDL_NUM_SCANCODES);
}

bool Input::key_down(SDL_Scancode scanCode)
{
	return (key_state[scanCode] == 1 && last_key_state[scanCode] == 0);
}

void Input::init()
{
	
	pad == NULL;

	key_state = (Uint8*)new Uint32[SDL_NUM_SCANCODES]();
	last_key_state = (Uint8*)new Uint32[SDL_NUM_SCANCODES]();
	std::memcpy(key_state, SDL_GetKeyboardState(NULL), sizeof(Uint32) * SDL_NUM_SCANCODES);
	std::memset(last_key_state, 0, sizeof(Uint32) * SDL_NUM_SCANCODES);

}
