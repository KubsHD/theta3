#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <render/renderer.h>

class Sprite : public Component {

public:

	bool flip = false;

	Sprite() = default;
	Sprite(String texPath);

	Texture* tex;

	void update() override;
	void render(Renderer* ren) override;
};