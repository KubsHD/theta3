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
	
	void update() override;

	void render(Renderer* ren) override;
};