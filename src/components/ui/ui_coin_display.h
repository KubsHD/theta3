#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <components/wave_system.h>


class UICoinDisplay : public Component
{
public:
	Texture* tex;
	UICoinDisplay()
	{
		tex = Asset::load_texture("sakiew.png");

	};

	String text_money, text_game_time;
	Vec2 pos;

	void update() override
	{
		auto game_time = Wave::round_time;
		text_game_time = std::to_string(game_time / 60) + ":" + std::to_string(game_time % 60);

		auto money = entity->world->get("Player")->get<Player>()->money;
		text_money = std::to_string(money);
	}


	void render(Renderer* ren) override
	{
		// Money display
		pos = Vec2(40, 100);
		ren->draw_tex(tex, Vec2(pos));
		ren->draw_text(text_money, Renderer::DefaultFont, Vec2(pos.x + tex->size.x + 10, pos.y - 14));
	
		// Game time
		ren->draw_text(text_game_time, Renderer::DefaultFont, Vec2(640, 20));

	}

};

