/*****************************************************************//**
 * \file   effects.h
 * \brief  component for creating visual effects 
 * 
 * \author staniekk
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

	/// <summary>
	/// duration of the effect
	/// </summary>
	int duration;

	bool follow, is_sprite, is_anim;
	Entity* player_ref;

	/// <summary>
	/// animator components
	/// </summary>
	Animator* anim;

	/// <summary>
	/// sprite component
	/// </summary>
	Sprite* sprite;

	/// <summary>
	/// name of the effect
	/// </summary>
	String name;
	
	/// <summary>
	/// offset of the effect from the player
	/// </summary>
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

