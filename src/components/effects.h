#pragma once

#include <core/types.h>
#include <SDL_stdinc.h>
#include <components/animator.h>
#include <components/sprite.h>
#include <components/player.h>


class Player;

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
	Effect(Entity* player_ref, String name)
	{
		this->name = name;

		duration = -1;
		follow = true;
		this->player_ref = player_ref;

		player_offset = player_ref->get<Player>()->player_offset;

		is_sprite = false;
		is_anim = false;
	}

	void init() override
	{	
		if (sprite = this->entity->get<Sprite>())
		{
			sprite->enabled = true;
			is_sprite = true;
		}
		if (anim = this->entity->get<Animator>())
		{
			anim->play_anim(name);
			is_anim = true;
		}


	}

	void update() override
	{
		if (is_sprite)
			entity->position = Vec2(player_ref->position.x - sprite->tex->size.x / 2,
				player_ref->position.y - sprite->tex->size.y / 2) + player_offset;
		
		if (is_anim)
		{
			entity->position = Vec2(player_ref->position.x - anim->get_frame_size().x / 2,
				player_ref->position.y - anim->get_frame_size().y / 2) + player_offset;
		}
	}

	void render(Renderer* ren) override
	{

	}
};

