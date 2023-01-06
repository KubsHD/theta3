#pragma once

#include <core/types.h>
#include <core/ecs.h>

class UIHpBar : public Component
{
public:
	UIHpBar() = default;

	float width = 0.0f;

	void update() override
	{
		GameScene* scn = ((GameScene*)this->entity->world);

		width = scn->player_ref->get<Player>()->health * 9.6f;
	}


	void render(Renderer* ren) override
	{
		ren->draw_box(Vec2(0, 530), Vec2(width, 50), Vec3(1, 0.2f, 0), true);
	}

};

