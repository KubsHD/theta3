#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <render/renderer.h>
#include <components/animator.h>

class PlayerMovement : public Component {
public:
	bool is_running, is_attacking;
	PlayerMovement() = default;
	PlayerMovement(float speed);


	float speed = 1.0f;
	
	void init() override;
	void update() override;

	void render(Renderer* ren) override;
};