#pragma once

#include <core/types.h>
#include <core/ecs.h>

class UIHpBar : public Component
{
public:
	UIHpBar() = default;


	void update() override
	{
	}


	void render(Renderer* ren) override
	{
		ren->draw_box(Vec2(0, 0), Vec2(960, 100), Vec3(0, 1, 0), true);
	}

};

