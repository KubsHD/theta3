#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <render/Renderer.h>
#include <functional>

class UIButton : public Component {
	String m_text;
public:
	UIButton() = default;
	UIButton(String text) : m_text(text) {};

	std::function<void()> on_clicked;

	float opacity = 1.0f;
	bool selected;

	void update() override
	{
		//throw std::logic_error("The method or operation is not implemented.");
	}


	void render(Renderer* ren) override
	{
		ren->draw_text(m_text, Renderer::DefaultFont, entity->position, selected ? opacity : opacity * 0.5);
	}

};
