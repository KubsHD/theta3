#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <stdlib.h>
#include <SDL_stdinc.h>
#include <core/log.h>

#include <components/animator.h>
#include <components/collider.h>
#include <core/audio.h>
#include <core/asset.h>
#include <components/player.h>
#include <render/Renderer.h>


class Player;

enum GUN_TYPE { SHOTGUN, PISTOL, MACHINE_GUN, CROSSBOW };

class Gun : public Component
{ 
public:
	Vec2 last_dead_enemy_pos;

	// backend
	float attack_cooldown;
	float damage;
	int magazine_capacity;
	int bullets_left;

	// Audio
	Sound* shot, on_hit;
	Entity* enemy;
	Collider* collider;


	Gun() = default;
	Gun(Entity* enemy_ref)
	{
		enemy = enemy_ref;
		last_dead_enemy_pos = Vec2(0, 0);
		attack_cooldown = 0;
		magazine_capacity = 0;
		bullets_left = 0;
		damage = 0;
	}

	void init() override
	{
		entity->position = enemy->position;
		collider = this->entity->get<Collider>();
		this->entity->get<Animator>()->play_anim("gun_shotgun");
	}

	void update() override
	{
		if (collider->check_sphere(Vec2(this->entity->position.x + collider->size.x/2,
			this->entity->position.y + collider->size.y/2), 20.0f, CollisionTag::Player))
		{
			log_info("you picked up A GUN OMG");
			this->entity->world->remove(this->entity);
				
		}
	}

	void render(Renderer* ren) override
	{
	}

	void gun_choose_type(int gun_type);
};
