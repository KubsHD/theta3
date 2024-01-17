/*****************************************************************//**
 * \file   dmg_popup.h
 * \brief  this component create dmg number pop up in game
 * 
 * \date   January 2023
 *********************************************************************/
#pragma once 

#include <core/types.h>
#include <core/ecs.h>

#include <render/Renderer.h>
/// <summary>
/// this class is respinsible for dmg text pop up
/// </summary>
class TextPopup : public Component
{

	float timer;
	float opacity = 1.0f;

	float vel = 1.0f;
public:

	String text;
	
	// Constructors
	TextPopup() = default;

	// Maintenance
	void update() override
	{
		timer += 1;
		
		entity->position += Vec2(0, -vel);

		if (timer > 50)
			opacity -= 0.01f;


		if (opacity <= 0.0f)
			this->entity->world->remove(this->entity);
	
	};

	void render(Renderer* ren) override
	{
		ren->draw_text(text, Renderer::DefaultFont, entity->position, 1.0f, opacity);
	};
};

namespace Factory {
	void CreateTextPopup(Scene* scn, Vec2 pos, String textToPopup);
}