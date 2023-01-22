/*****************************************************************//**
 * \file   gun.h
 * \brief  component responsible for creating a gun that can be collected by stepping on it
 * 
 * \date   January 2023
 *********************************************************************/
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

/// <summary>
/// enum for gun types
/// </summary>
enum GUN_TYPE { BROOM, PISTOL, SHOTGUN, MACHINE_GUN, CROSSBOW };

/// <summary>
/// creating a gun that can be collected by stepping on it
/// </summary>
class Gun : public Component
{ 
public:
	Vec2 last_dead_enemy_pos;

	// Audio
	Entity* enemy;
	Entity* player;
	Collider* collider;
	String weapon_sprite;

	Gun() = default;
	Gun(Entity* enemy_ref, Entity* player_ref)
	{
		player = player_ref;
		enemy = enemy_ref;
		last_dead_enemy_pos = Vec2(0, 0);
	}

	/// <summary>
	/// used to choose dropped gun type
	/// </summary>
	/// <param name="gun_type">desired gun type</param>
	void gun_choose_type(int gun_type);

	void init() override;
	void update() override;
	void render(Renderer* ren) override;,
};
