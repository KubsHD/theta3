#pragma once 

#include <core/types.h>
#include <core/ecs.h>
#include "enemy.h"
#include <iostream>


class Player : public Enemy
{
public:
	// Custom variables
	int health, souls, speed, money;
	float damage_melee;

	// Constructors
	Player();


	// Maintenance
	void update() override;
	void render(Renderer* ren) override;
};