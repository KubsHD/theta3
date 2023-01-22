/*****************************************************************//**
 * \file   enemy_adult.h
 * \brief  component resposible for enemy type: Policeman
 *
 * \date   January 2023
 *********************************************************************/
#pragma once 

#include <core/types.h>
#include <core/ecs.h>
#include "enemy.h"

 /// <summary>
 /// class responsible for enemies stats and AI
 /// </summary>
class Policeman : public Enemy
{
public:
	// Custom variables
	Vec2 temp_pos;
	Entity* player;
	bool running;
	float damage_gun, temp_val;

	// Constructors
	Policeman() = default;
	Policeman(Entity* player_ref);

	// Maintanance
	void update() override;
	void render(Renderer* ren) override
	{
		Enemy::render(ren);
	};
};