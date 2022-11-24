#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <stdlib.h>
#include <SDL_stdinc.h>

#include <components/animator.h>
#include <components/sprite.h>

class Enemy : public Component
{
public:
	// backend
	float facing_angle, temp;

	// gameplay
	float health, damage, souls, speed;
	Enemy() = default;

	void update() override 
	{
	}

	void render(Renderer* ren) override
	{
		// renderowanie
	}
	
	void flip_sprite();
};

