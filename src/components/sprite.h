#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <render/renderer.h>

class Sprite : public Component {

public:

	Sprite() = default;
	Sprite(String texPath) {
		tex = new Texture(texPath);
	};

	Texture* tex;

	void update() override {

	};

	void render(Renderer* ren) override {
		ren->draw_tex(tex, entity->position);
		ren->draw_box(entity->position, tex->size, Vec3(0.1f, 0.1f, 1.0f));
	};
};