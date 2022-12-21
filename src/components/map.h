#pragma once

#include <core/types.h>
#include <SDL_stdinc.h>
#include <components/animator.h>
#include <components/sprite.h>


class Player;

class MapGenerator : public Component
{
public:
	Entity* player_ref;


	MapGenerator() = default;

	void init() override
	{	

	}

	void update() override
	{
		if (player_ref != NULL)
		{



		}
	};

	void render(Renderer* ren) override
	{
		
	}
};

