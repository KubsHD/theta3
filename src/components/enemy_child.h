/*****************************************************************//**
 * \file   enemy_adult.h
 * \brief  component resposible for enemy type: Child
 *
 * \author staniekk
 * \date   January 2023
 *********************************************************************/
#pragma once 

#include <core/types.h>
#include <core/ecs.h>
#include "enemy.h"
#include <SDL_stdinc.h>


 /// <summary>
 /// class responsible for enemies stats and AI
 /// </summary>
class Child : public Enemy
{
public:
	// Custom Variables
	Entity* player;
	Vec2 temp_pos;
	float temp_val;
	float delta_x, delta_y;
	
	// Constructors
	Child() = default;
	Child(Entity* player_ref);

	// Maintenance
	void update() override;
	void render(Renderer* ren) override
	{
		Enemy::render(ren);
	};
};