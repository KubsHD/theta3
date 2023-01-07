#pragma once

#include <core/types.h>
#include <SDL_stdinc.h>
#include <components/animator.h>
#include <components/sprite.h>


class Player;

class Effect : public Component
{
public:
	int duration;
	bool follow;
	Entity* player_ref;
	Animator* anim;
	Sprite* sprite;
	String name;

	Effect() = default;
	Effect(Entity* player_ref, String name)
	{
		this->name = name;

		duration = -1;
		follow = true;
		this->player_ref = player_ref;
	}

	void init() override
	{	
		if (sprite = this->entity->get<Sprite>())
			sprite->enabled = true;
		if (anim = this->entity->get<Animator>())
			anim->play_anim(name);


	}

	void update() override
	{
		entity->position = Vec2(player_ref->position.x - 480, player_ref->position.y - 290);
	}

	void render(Renderer* ren) override
	{

	}
};

