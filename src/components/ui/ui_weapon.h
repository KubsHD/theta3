/*****************************************************************//**
 * \file   ui_weapon.h
 * \brief  displays selected weapon
 * 
 * \date   January 2023
 *********************************************************************/
#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <core/asset.h>
#include <render/Renderer.h>
#include <vector>


/// <summary>
/// displays selected weapon
/// </summary>
class UIWeaponDisplay : public Component
{
public:

	/// <summary>
	/// Textures of the weapons
	/// </summary>
	std::vector <Texture*> tex;
	
	/// <summary>
	/// Player reference
	/// </summary>
	Player* player;

	int temp;
	int selected;
	float opacity;

	UIWeaponDisplay()
	{
		temp = 0;
		selected = 0;

		tex.push_back(Asset::load_texture("icon_broom.png"));
		tex.push_back(Asset::load_texture("icon_pistol.png"));
		tex.push_back(Asset::load_texture("icon_shotgun.png"));
		tex.push_back(Asset::load_texture("icon_machine_gun.png"));
		tex.push_back(Asset::load_texture("icon_crossbow.png"));
	};


	void init() override
	{
		player = entity->world->get("Player")->get<Player>();
	}

	void update() override
	{
		selected = player->selected_weapon;
	}

	void render(Renderer* ren) override
	{		
		if (selected < tex.size())
			ren->ui_draw_tex(tex[selected], Vec2(20, 50));
	}
};
