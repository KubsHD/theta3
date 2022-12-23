#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <render/Renderer.h>
#include <functional>

class UIButton : public Component {
	String m_text;
public:
	UIButton() = default;
	UIButton(String text) : m_text(text) {
		button_shader = new Shader("button");
	};

	std::function<void()> on_clicked;

	float opacity = 1.0f;
	float scale = 1.0f;
	bool selected;

	Shader* button_shader;

	void update() override
	{
		//throw std::logic_error("The method or operation is not implemented.");
	}


	void render(Renderer* ren) override
	{
		if (selected)
			ren->draw_box_s(entity->position + Vec2(0, 10), Vec2(m_text.size() * 25, 50), Vec3(0, 0, 0), button_shader);
		ren->draw_text(m_text, Renderer::DefaultFont, entity->position, scale, selected ? opacity : opacity * 0.5);
	}

};
