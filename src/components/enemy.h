#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <stdlib.h>
#include <SDL_stdinc.h>

#include <components/animator.h>
#include <components/sprite.h>	
#include <core/audio.h>
#include <components/player.h>

class Player;

class Enemy : public Component
{
public:
	// backend
	float facing_angle, temp;
	Sound* audio_death;
	Player* player;
	bool is_dead = false;

	// gameplay
	float health, damage, souls, speed, money;

	Enemy() = default;

	void flip_sprite();
	void on_death();

	void update() override 
	{
		on_death();
		flip_sprite();
	}

	void render(Renderer* ren) override
	{
		// renderowanie
	}
};

