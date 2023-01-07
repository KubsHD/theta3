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

	bool is_on_broom = false;

	float speed = 1.0f;

	float melee_damage = 15.0f;
	float knockback_rate = 1.0f;

	float speed_base = 2.0f;
	float speed_when_attacking = 0.2f;
	
	void init() override;
	void update() override;

	void render(Renderer* ren) override;
private:
	float speed_on_broom = 4.0f;
};