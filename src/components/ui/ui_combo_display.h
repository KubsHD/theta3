/*****************************************************************//**
 * \file   ui_combo_display.h
 * \brief  displays number of points, animated background under it, and multiplier
 * 
 * \date   January 2023
 *********************************************************************/
#pragma once 

#include <core/types.h>
#include <core/ecs.h>
#include <core/asset.h>

#include <lib/glad/glad.h>

#include <render/Renderer.h>


/// <summary>
///  displays number of points, animated background under it, and multiplier
/// </summary>
class UIComboDisplay : public Component
{
	Texture* noise;
	Texture* gradient;
	Shader* flame;

public:
	Vec2 widget_position = Vec2(0,0);
	
	// Constructors
	UIComboDisplay()
	{
		flame = Asset::load_shader("flame");
		noise = Asset::load_texture("texture/noise/Perlin/p7.png");
		gradient = Asset::load_texture("texture/gradient/Basic/Horizontal_1-256x256.png");

	}

	// Maintenance
	void update() override
	{

	};

	void render(Renderer* ren) override
	{
		glUseProgram(flame->get_id());

		GLint texLoc = glGetUniformLocation(flame->get_id(), "u_tex");
		glUniform1i(texLoc, 0);

		texLoc = glGetUniformLocation(flame->get_id(), "u_tex2");
		glUniform1i(texLoc, 1);

		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, gradient->id);

		glActiveTexture(GL_TEXTURE0);
		ren->draw_tex_s(noise, widget_position + Vec2(-5,20), Vec2(140, 70), flame);
		ren->draw_text("COMBO", Renderer::DefaultFont, widget_position + Vec2(30, 20), 1.0f, 1.0f);
		ren->draw_text("2x", Renderer::DefaultFont, widget_position + Vec2(0, 50), 1.0f, 1.0f);
		ren->draw_text("000000", Renderer::DefaultFont, widget_position + Vec2(40, 60), 1.0f, 1.0f);
	};
};