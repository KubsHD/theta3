#pragma once 

#include <core/types.h>
#include <core/ecs.h>
#include "enemy.h"
#include <iostream>


class Player : public Component
{
public:
	// Custom variables
	int health, speed, money;
	float damage_melee;

	// Constructors
	Player();


	// Maintenance
	void update() override;
	void render(Renderer* ren) override;
};