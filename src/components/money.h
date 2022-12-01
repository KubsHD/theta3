#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <stdlib.h>
#include <SDL_stdinc.h>

#include <components/animator.h>
#include <components/sprite.h>
#include <core/audio.h>
#include <iostream>

class Money : public Component
{
public:
	Entity* player_ref;


	Money() = default;

	Money(Entity* player_ref)
	{
		this->player_ref = player_ref;
	}

	void update() override
	{
	}

	void render(Renderer* ren) override
	{
		this->entity->get<Animator>()->play_anim("coin");
	}
};

