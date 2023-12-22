/*****************************************************************//**
 * \file   ui_coin_display.h
 * \brief  displays game time, money gathered, and number of enemies killed
 * 
 * \date   January 2023
 *********************************************************************/
#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <components/wave_system.h>


/// <summary>
/// UI elements: game time, money gathered, and number of enemies killed
/// </summary>
class UICoinDisplay : public Component
{
public:
	
	/// <summary>
	/// Text for money, game time, kills
	/// </summary>
	String text_money, text_game_time, text_kills;
	
	/// <summary>
	/// Position of money icon, kills icon
	/// </summary>
	Vec2 pos_money, pos_kills;
	
	/// <summary>
	/// Texture for money icon
	/// </summary>
	Texture* tex_money;
	
	/// <summary>
	/// Texture for skull icon
	/// </summary>
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

		auto kills = entity->world->get("Player")->get<Player>()->kill_count;
		text_kills = std::to_string(kills);
	}


	void render(Renderer* ren) override
	{
		// Money display
		ren->ui_draw_tex(tex_money, Vec2(pos_money));
		ren->ui_draw_text(text_money, Renderer::DefaultFont, Vec2(pos_money.x + tex_money->size.x + 10, pos_money.y - 14));

		ren->ui_draw_tex(tex_skull, Vec2(pos_kills));
		ren->ui_draw_text(text_kills, Renderer::DefaultFont, Vec2(pos_kills.x + tex_skull->size.x + 10, pos_kills.y - 14));

	
		// Game time
		ren->ui_draw_text(text_game_time, Renderer::DefaultFont, Vec2(640, 20));
	}

};

