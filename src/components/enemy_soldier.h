#pragma once 

#include <core/types.h>
#include <core/ecs.h>
#include "enemy.h"
#include <iostream>


class Soldier : public Enemy
{
public:
	// Custom variables
	Vec2 pos;
	Entity* player;
	bool running;
	float damage_gun, damage_grenade;

	// Constructors
	Soldier() = default;
	Soldier(Entity* player_ref);

	// Maintenance
	void update() override;
	void render(Renderer* ren) override
	{
		Enemy::render(ren);
	};
};