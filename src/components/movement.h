#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <render/renderer.h>
#include <components/animator.h>

class PlayerMovement : public Component {
public:
	PlayerMovement() = default;
	PlayerMovement(float speed) : speed(speed) {};


	float speed = 1.0f;
	
	void update() override {

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

	void render(Renderer* ren) override {

	};
};