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

	Effect() = default;
	Effect(Entity* player_ref);

	void init() override
	{	}

	void update() override
	{
		entity->position = Vec2(player_ref->position.x - 480, player_ref->position.y - 290);
	}

	void render(Renderer* ren) override
	{
		this->entity->get<Animator>()->play_anim("effects_rain");
	}
};

