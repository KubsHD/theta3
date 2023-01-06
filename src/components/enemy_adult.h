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
	int temp_val;
	bool can_walk;

	// Constructors
	Adult() = default;
	Adult(Player* player_ref);

	void on_death();

	// Maintenance
	void init() override;
	void update() override;
	void render(Renderer* ren) override
	{
		Enemy::render(ren);
	};

};