#include "movement.h"

#include <SDL.h>
#include <components/animator.h>
#include <components/sprite.h>
#include <core/input.h>


enum PLAYER_STATES
{
	IDLE, RUN, ATTACK
};


String player_anim[3] =
{
	"witch_idle",
	"witch_run",
	"anm_witch_atk_R"
};


void PlayerMovement::update()
{

	if (Input::key_down(SDL_SCANCODE_SPACE))
	{
		is_attacking = true;
		this->entity->get<Sprite>()->enabled = false;
		
		this->entity->get<Animator>()->play_anim(player_anim[ATTACK], [this]() {
			this->entity->get<Sprite>()->enabled = true, is_attacking = false;
			});
	}


	is_running = false;
	if (Input::key_held(SDL_SCANCODE_D)) {
		entity->position.x += speed;
		is_running = true;
		entity->flip = false;
	}

	if (Input::key_held(SDL_SCANCODE_S)) {
		entity->position.y += speed;
		is_running = true;
	}

	if (Input::key_held(SDL_SCANCODE_A)) {
		entity->position.x -= speed;
		is_running = true;
		entity->flip = true;
	}

	if (Input::key_held(SDL_SCANCODE_W)) {
		entity->position.y -= speed;
		is_running = true;
	}


	if (is_running == true && is_attacking == false)
	{
		this->entity->get<Sprite>()->enabled = false;

		this->entity->get<Animator>()->play_anim(player_anim[RUN], [this]() {
			this->entity->get<Sprite>()->enabled = true;
			});
	}
	else if (is_attacking == false)
	{
		this->entity->get<Sprite>()->enabled = false;

		this->entity->get<Animator>()->play_anim(player_anim[IDLE], [this]() {
			this->entity->get<Sprite>()->enabled = true;
			});
	}


};


void PlayerMovement::render(Renderer* ren)
{

}

