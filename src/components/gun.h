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
	Entity* player;
	Collider* collider;
	String anim;
	String sprite;
	

	Gun() = default;
	Gun(Entity* enemy_ref, Entity* player_ref)
	{
		player = player_ref;
		enemy = enemy_ref;
		last_dead_enemy_pos = Vec2(0, 0);
		attack_cooldown = 0;
		magazine_capacity = 0;
		bullets_left = 0;
		damage = 0;
	}

	void gun_choose_type(int gun_type);

	void init() override;
	void update() override;
	void render(Renderer* ren) override;
};
