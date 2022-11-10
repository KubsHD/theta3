#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <stdlib.h>
#include <time.h>


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
		// zachowanie
	}

	void render(Renderer* ren) override
	{
		// renderowanie
	}
	
};

