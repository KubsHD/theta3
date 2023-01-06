#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <stdlib.h>
#include <SDL_stdinc.h>

#include <components/animator.h>
#include <components/sprite.h>	
#include <core/audio.h>
#include <core/asset.h>
#include <components/player.h>
#include <render/Renderer.h>


class Player;

class Enemy : public Component
{
public:
	// backend
	float facing_angle, temp, text_opacity = 1;
	int attack_cooldown;

	// Audio
	Sound* audio_death;
	Sound* audio_damage_dealt;
	Sound* audio_damage_recived;

	Collider* collider;
	Vec2 text_pos;
	Player* player;
	bool is_dead = false;

	// movement
	float delta_x, delta_y;

	// gameplay
	float health, damage, souls, speed, money;

	Enemy() = default;
	Enemy(Player* player_ref)
	{
		player = player_ref;
	}

	void init() override
	{
		//collider = entity->get<Collider>();
		//// todo zmienic na rozmiar spritea
		//collider->size = Vec2(32, 32);
		//collider->tag = CollisionTag::Enemy;
	}

	void flip_sprite();
	void on_death();
	void handle_collision();

	void update() override 
	{
		//text_pos.y -= 0.1f;
	

		on_death();
		flip_sprite();
	}

	void render(Renderer* ren) override
	{
		// renderowanie
		//if (is_dead == true) {
		//	ren->draw_text("elooo", Renderer::DefaultFont, text_pos, 0.8, 1);
		//	//text_opacity -= 0.1f;
		//}
	}
	void take_damage(float melee_damage, float knockback_rate);
};

