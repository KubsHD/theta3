/*****************************************************************//**
 * \file   wave_system.h
 * \brief  component responsible for spawning enemy waves
 * 
 * \date   January 2023
 *********************************************************************/
#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <components/collider.h>

#include <components/enemy_adult.h>
#include <components/enemy_child.h>
#include <components/enemy_policeman.h>
#include <components/enemy_soldier.h>
#include <components/enemy_fatass.h>
#include <components/effects.h>


/// <summary>
/// spawns wave of enemies at the chosen point of game
/// </summary>
class Wave : public Component
{
public: 

	RTTI_COMPONENT_NAME(Wave)

	Entity* player;

	int waveID, frames;
	float time_between_spawns_seconds, enemy_spawn_multiplier;
	static unsigned int round_time;

	Sound* thunder;
	//Effects;
	Entity* fog;

	// Maintenance
	Wave() = default;
	Wave(Entity* player);

	void init() override;
	void update()  override;
	void render(Renderer* ren) override;
	
	/// <summary>
	/// used to spawn wave of enemies consisting of desired amount of enemies
	/// </summary>
	void wave_spawn();
};