#pragma once 

#include <core/types.h>
#include <core/ecs.h>
#include "enemy.h"
#include <SDL_stdinc.h>

// Bullet is an enemy with body damage on contact with player;
// Player can destroy bullets with attacs
class Bullet : public Enemy
{
public:
	// Custom Variables
	Vec2 temp_pos;
	Entity* player;
	bool is_destructible;
	bool first_frame;

	// Constructors
	Bullet() = default;
	Bullet(Entity* player_ref);

	// Maintenance
	void update() override;
	void render(Renderer* ren) override
	{
		Enemy::render(ren);
	};
};