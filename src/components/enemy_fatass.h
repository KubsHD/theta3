/*****************************************************************//**
 * \file   enemy_adult.h
 * \brief  component resposible for enemy type: Fatass
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
class Fatass : public Enemy
{
public:
	// Custom variables
	Vec2 temp_pos;
	Entity* player;

	// Constructors
	Fatass() = default;
	Fatass(Entity* player_ref);

	// Maintenance
	void update() override;
};