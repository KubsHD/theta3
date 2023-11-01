#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <render/Renderer.h>
#include <functional>

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/gtx/compatibility.hpp>
#include <core/asset.h>


class UIShopCard : public Component {
	String m_text;
public:
	UIShopCard() = default;
	UIShopCard(String text) : m_text(text) {
		button_shader = Asset::load_shader("button");
	};

	bool selected;

	Shader* button_shader;

	Vec2 offset;

	void update() override
	{
		offset.x = 0.0f;
		offset.y = glm::lerp(offset.y, selected ? -60.0f : 0.0f, 0.07f);
		//throw std::logic_error("The method or operation is not implemented.");
	}


	void render(Renderer* ren) override
	{
		ren->draw_box(entity->position + offset, Vec2(200, 500), Vec3(0.2f, 0.2f, 0), true);
		//ren->draw_text("test", Renderer::DefaultFont, entity->position + offset);
	}

};
