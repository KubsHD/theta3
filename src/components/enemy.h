#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <stdlib.h>
#include <SDL_stdinc.h>

#include <components/animator.h>
#include <components/sprite.h>	
#include <core/audio.h>
#include <components/player.h>
#include <render/Renderer.h>


class Player;

class Enemy : public Component
{
public:
	// backend
	float facing_angle, temp, text_opacity = 1;
	Sound* audio_death;
	Player* player;
	bool is_dead = false;

	Vec2 text_pos;
	int t = 0;

	// gameplay
	float health, damage, souls, speed, money;

	Enemy() = default;

	void init() override
	{
		text_pos = entity->position;
	}

	void flip_sprite();
	void on_death();

	void update() override 
	{
		//text_pos.y -= 0.1f;
	

		on_death();
		flip_sprite();
	}

	void render(Renderer* ren) override
	{
		// renderowanie
		if (is_dead == true) {
			ren->draw_text("elooo", Renderer::DefaultFont, text_pos, 0.8, 1);
			//text_opacity -= 0.1f;
		}
	}
};

