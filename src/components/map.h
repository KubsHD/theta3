/*****************************************************************//**
 * \file   map.h
 * \brief  this component is responsible for creating map
 * 
 * \date   January 2023
 *********************************************************************/
#pragma once

#include <core/types.h>
#include <SDL_stdinc.h>
#include <components/animator.h>
#include <components/sprite.h>
#include <core/asset.h>
#include <lib/imgui/imgui.h>


class Player;
/// <summary>
/// class responsible for generating map
/// </summary>
class MapGenerator : public Component
{
public:
	Entity* player_ref;

	/// <summary>
	/// textures of the map
	/// </summary>
	Vector<Texture*> map_textures;

	/// <summary>
	/// map of positions to draw map at
	/// </summary>
	UnorderedMap<Vec2, int> positions_to_draw_map_at;

	Vec2 player_pos_during_last_map_update = Vec2(100000, 10000);

	int a = 300;

	MapGenerator() = default;
	MapGenerator(Entity* player)
	{
		player_ref = player;
	}

	void init() override
	{	
		map_textures.push_back(Asset::load_texture("map/main/png/Level_0.png"));
	}

	long roundDown(long n, long m) {
		return n >= 0 ? (n / m) * m : ((n - m + 1) / m) * m;
	}
	void update() override
	{
		auto player_pos = player_ref->position;

		Vec2 map_pos = Vec2(0,0);
		map_pos.x = roundDown(player_pos.x, 960);
		map_pos.y = roundDown(player_pos.y, 544);

		auto delta = (player_pos - player_pos_during_last_map_update);

		if (glm::length(delta) > a)
		{
			positions_to_draw_map_at.clear();

			auto addIfNotNegative = [&](const Vec2& pos)
				{
					if (pos.x >= 0 && pos.y >= 0)
					{
						positions_to_draw_map_at.insert({ pos, 0 });
					}
				};

			// Add positions only if they are not negative
			addIfNotNegative(map_pos);
			addIfNotNegative(map_pos + Vec2(960, 544));
			addIfNotNegative(map_pos - Vec2(960, 544));
			addIfNotNegative(map_pos + Vec2(960, -544));
			addIfNotNegative(map_pos - Vec2(960, -544));
			addIfNotNegative(map_pos + Vec2(960, 0));
			addIfNotNegative(map_pos - Vec2(960, 0));
			addIfNotNegative(map_pos + Vec2(0, 544));
			addIfNotNegative(map_pos - Vec2(0, 544));

			player_pos_during_last_map_update = player_pos;
		}
	};

	void render(Renderer* ren) override
	{
		{
			if(	ImGui::Begin("Map dbg"))
			{
				ImGui::InputInt("a", &a);
			}
			ImGui::End();
		}

		for (auto [pos, idx] : positions_to_draw_map_at)
		{
			ren->draw_tex(map_textures[idx], pos);
		}
	}
};

