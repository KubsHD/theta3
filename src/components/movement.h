#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <render/renderer.h>

class Movement : public Component {
public:
	Movement() = default;


	float speed = 1.0f;
	
	void update() override {

		if (Input::key_held(SDL_SCANCODE_RIGHT))
			entity->position.x += speed;

		if (Input::key_held(SDL_SCANCODE_DOWN))
			entity->position.y += speed;

		if (Input::key_held(SDL_SCANCODE_LEFT))
			entity->position.x -= speed;

		if (Input::key_held(SDL_SCANCODE_UP))
			entity->position.y -= speed;
	};

	void render(Renderer* ren) override {

	};
};