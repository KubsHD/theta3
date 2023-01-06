#pragma once

#include <core/types.h>
#include <core/ecs.h>

class UICoinDisplay : public Component
{
public:
	UICoinDisplay() = default;

	String text;

	void update() override
	{
		auto money = entity->world->get("Player")->get<Player>()->money;
		text = "Kasa: " + std::to_string(money);
	}


	void render(Renderer* ren) override
	{
		ren->draw_text(text, Renderer::DefaultFont, Vec2(80,80));
	}

};

