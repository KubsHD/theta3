/*****************************************************************//**
 * \file   ui_button.h
 * \brief  draws rectangle as moving background for menu options
 * 
 * \date   January 2023
 *********************************************************************/
#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <render/Renderer.h>
#include <functional>
#include <core/asset.h>


/// <summary>
/// Creates a UI button
/// </summary>
class UIButton : public Component {

	/// <summary>
	/// Text of the button
	/// </summary>
	String m_text;
public:
	UIButton() = default;
	UIButton(String text) : m_text(text) {
		button_shader = Asset::load_shader("button");
	};

	
	/// <summary>
	/// Called when the button is clicked
	/// </summary>
	std::function<void()> on_clicked;

	/// <summary>
	/// Opacity of the button
	/// </summary>
	float opacity = 1.0f;

	/// <summary>
	/// Scale of the button
	/// </summary>
	float scale = 1.0f;

	/// <summary>
	/// Is the button selected
	/// </summary>
	bool selected;

	/// <summary>
	/// Shader used to draw the button
	/// </summary>
	Shader* button_shader;

	void update() override
	{
		//throw std::logic_error("The method or operation is not implemented.");
	}


	void render(Renderer* ren) override
	{
		if (selected)
			ren->draw_box_s(entity->position + Vec2(-10, -4), Vec2(m_text.size() * 15, 50), Vec3(0, 0, 0), button_shader);
		ren->draw_text(m_text, Renderer::DefaultFont, entity->position, scale, selected ? opacity : opacity * 0.5);
	}

};
