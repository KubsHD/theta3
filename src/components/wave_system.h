#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <components/collider.h>

#include <components/enemy_adult.h>
#include <components/enemy_child.h>
#include <components/enemy_policeman.h>
#include <components/enemy_soldier.h>
#include <components/enemy_fatass.h>

class Wave : public Component
{
public: 
	Entity* player;
	int waveID, round_time, frames;

	// Maintenance
	Wave() = default;
	Wave(Entity* player);

	void init() override;
	void update()  override;
	void render(Renderer* ren) override;

	void wave_spawn();
};