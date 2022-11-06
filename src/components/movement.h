#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <render/renderer.h>

class Movement : public Component {
public:
	Movement() = default;
	Movement(float speed) : speed(speed) {};


	float speed = 1.0f;
	
	void update() override {

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