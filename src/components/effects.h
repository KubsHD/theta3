/*****************************************************************//**
 * \file   effects.h
 * \brief  component for creating visual effects 
 * 
 * \date   January 2023
 *********************************************************************/
#pragma once

#include <core/types.h>
#include <SDL_stdinc.h>
#include <components/animator.h>
#include <components/sprite.h>
#include <components/player.h>
#include <lib/imgui/imgui.h>


class Player;

/// <summary>
/// creates, and displays visual effects
/// </summary>
class Effect : public Component
{
public:
	int duration;
	bool follow, is_sprite, is_anim;
	Entity* player_ref;
	Animator* anim;
	Sprite* sprite;
	String name;
	Vec2 player_offset;

	Effect() = default;
	Effect(Entity* player_ref, String name);

	/// <summary>
	/// plays the effect once
	/// </summary>
	void play_once();

	void init() override;
	void update() override;
	void render(Renderer* ren) override;
};

