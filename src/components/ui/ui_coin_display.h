#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <components/wave_system.h>


class UICoinDisplay : public Component
{
public:
	String text_money, text_game_time, text_kills;
	Vec2 pos_money, pos_kills;
	Texture* tex_money;
	Texture* tex_skull;
	
	
	UICoinDisplay()
	{
		tex_money = Asset::load_texture("sakiew.png");
		tex_skull = Asset::load_texture("icon_skull.png");

		pos_money = Vec2(32, 90);
		pos_kills = Vec2(32 , 135);
	};


	void update() override
	{
		auto game_time = Wave::round_time;
		text_game_time = std::to_string(game_time / 60) + ":" + std::to_string(game_time % 60);

		auto money = entity->world->get("Player")->get<Player>()->money;
		text_money = std::to_string(money);

		auto kills = entity->world->get("Player")->get<Player>()->enemies;
		text_kills = std::to_string(kills);
	}


	void render(Renderer* ren) override
	{
		// Money display
		ren->draw_tex(tex_money, Vec2(pos_money));
		ren->draw_text(text_money, Renderer::DefaultFont, Vec2(pos_money.x + tex_money->size.x + 10, pos_money.y - 14));

		ren->draw_tex(tex_skull, Vec2(pos_kills));
		ren->draw_text(text_kills, Renderer::DefaultFont, Vec2(pos_kills.x + tex_skull->size.x + 10, pos_kills.y - 14));

	
		// Game time
		ren->draw_text(text_game_time, Renderer::DefaultFont, Vec2(640, 20));




	}

};

