#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <core/asset.h>
#include <render/Renderer.h>
#include <vector>


class UIWeaponDisplay : public Component
{
public:

	std::vector <Texture*> tex;
	int temp;

	UIWeaponDisplay()
	{
		temp = 0;

		tex.push_back(Asset::load_texture("icon_broom.png"));
		tex.push_back(Asset::load_texture("icon_gun.png"));

	};


	void update() override
	{


	}

	void render(Renderer* ren) override
	{

		for (auto i : tex) {
			ren->draw_tex(i, Vec2(temp*i->size.x + (temp+1) * 20, 50));
			temp++;
		}
		temp = 0;
	}

};

