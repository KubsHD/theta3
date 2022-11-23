#pragma once 

#include <core/types.h>
#include <core/ecs.h>
#include "enemy.h"
#include <SDL_stdinc.h>
#include <components/animator.h>
#include <components/sprite.h>


class Adult : public Enemy
{
public:
	// Custom Variables
	Vec2 temp_pos;
	Entity* player;
	int temp_val;

	// Constructors
	Adult() = default;
	Adult(Entity* player_ref);

	// Maintenance
	void update() override;
	void render(Renderer* ren) override
	{
		Enemy::render(ren);
	};
};