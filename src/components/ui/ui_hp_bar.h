/*****************************************************************//**
 * \file   ui_hp_bar.h
 * \brief  displays health bar at the bottom of the screen
 * 
 * \author staniekk
 * \date   January 2023
 *********************************************************************/
#pragma once

#include <core/types.h>
#include <core/ecs.h>

/// <summary>
///  displays health bar at the bottom of the screen
/// </summary>
class UIHpBar : public Component
{
public:
	UIHpBar() = default;

	float width = 0.0f;

	void update() override
	{
		GameScene* scn = ((GameScene*)this->entity->world);

		width = scn->player_ref->get<Player>()->health * 12.8f;
	}


	void render(Renderer* ren) override
	{
		ren->draw_box(Vec2(0, 700), Vec2(width, 50), Vec3(1, 0.2f, 0), true);
	}

};

