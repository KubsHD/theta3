#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <render/Renderer.h>

class UIButton : public Component {
	String m_text;
public:
	UIButton() = default;
	UIButton(String text) : m_text(text) {};


	void update() override
	{
		//throw std::logic_error("The method or operation is not implemented.");
	}


	void render(Renderer* ren) override
	{
		ren->draw_text(m_text, Renderer::DefaultFont, entity->position, 0.4f);
	}

};
