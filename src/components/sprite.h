/*****************************************************************//**
 * \file   sprite.h
 * \brief  component responsible for sprite rendering
 * 
 * \date   January 2023
 *********************************************************************/
#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <render/renderer.h>

class Sprite : public Component {

public:

	bool flip = false;

	Sprite() = default;
	Sprite(String texPath);
	/// <summary>
	/// texture to create in game entities
	/// </summary>
	Texture* tex;

	/// <summary>
	/// used to choose sprite
	/// </summary>
	/// <param name="path">path to sprite file</param
	void change(String path);

	void update() override;
	void render(Renderer* ren) override;
};