/*****************************************************************//**
 * \file   movement.h
 * \brief  component responsible for player movement and shooting bullets
 * 
 * \date   January 2023
 *********************************************************************/

#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <render/renderer.h>
#include <components/animator.h>
#include <components/player.h>

/// <summary>
/// class responsible for player movement and shooting bullets
/// </summary>
class PlayerMovement : public Component {
public:
	bool is_running, is_attacking;
	Player* player;
	PlayerMovement() = default;
	PlayerMovement(Entity* player_ref, float speed);

	bool is_on_broom = false;

	float speed = 1.0f;

	float knockback_rate = 0.5f;

	float speed_base = 2.0f;
	float speed_when_attacking = 0.2f;

	void init() override;
	void update() override;
private:
	float speed_on_broom = 4.0f;
};