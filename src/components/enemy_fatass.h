#pragma once 

#include <core/types.h>
#include <core/ecs.h>
#include "enemy.h"


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
	void render(Renderer* ren) override
	{
		Enemy::render(ren);
	};
};