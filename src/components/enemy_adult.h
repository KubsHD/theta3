/*****************************************************************//**
 * \file   enemy_adult.h
 * \brief  component resposible for enemy type: Adult
 * 
 * \author staniekk
 * \date   January 2023
 *********************************************************************/
#pragma once 

#include <core/types.h>
#include <core/ecs.h>
#include "enemy.h"
#include <SDL_stdinc.h>
#include <components/animator.h>
#include <components/sprite.h>

/// <summary>
/// class responsible for enemies stats and AI
/// </summary>
class Adult : public Enemy
{
public:
	// Custom Variables
	Vec2 temp_pos;
	int temp_val;
	bool can_walk;

	// Constructors
	Adult() = default;
	/// <summary>
	/// Creates instance of enemy (type: Adult)
	/// </summary>
	/// <param name="player_ref">Reference to player class</param>
	Adult(Player* player_ref);

	void on_death();

	// Maintenance
	void init() override;
	void update() override;
	void render(Renderer* ren) override
	{
		//Enemy::render(ren);
	};

};