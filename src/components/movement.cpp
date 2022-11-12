#include "movement.h"

#include <SDL.h>
#include <components/animator.h>
#include <components/sprite.h>
#include <core/input.h>

void PlayerMovement::update()
{

	if (Input::key_down(SDL_SCANCODE_SPACE))
	{
		this->entity->get<Sprite>()->enabled = false;
		this->entity->get<Animator>()->play_anim("anm_witch_atk_R", [this]() {
			this->entity->get<Sprite>()->enabled = true;
			});
	}


	if (Input::key_held(SDL_SCANCODE_D))
		entity->position.x += speed;

	if (Input::key_held(SDL_SCANCODE_S))
		entity->position.y += speed;

	if (Input::key_held(SDL_SCANCODE_A))
		entity->position.x -= speed;

	if (Input::key_held(SDL_SCANCODE_W))
		entity->position.y -= speed;
};


void PlayerMovement::render(Renderer* ren)
{

}

