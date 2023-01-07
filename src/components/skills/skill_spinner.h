#pragma once

#include <core/types.h>
#include <render/Renderer.h>

class SkillSpinner : public Component
{
public:
	SkillSpinner() = default;

	Entity* plr_ref;

	SkillSpinner(Entity* plr)
	{
		plr_ref = plr;
	};

	~SkillSpinner() {}; 

	float dist = 100.0f;
	float speed = 2.0f;

	Vec2 pos;

	void update() override 
	{
		pos.y = plr_ref->position.y + dist * sin(get_time() * speed);
		pos.x = plr_ref->position.x + dist * cos(get_time() * speed);

		for (auto& ent : entity->get<Collider>()->check_sphere_list(pos, 50.0f, CollisionTag::Enemy))
		{
			ent->entity->get<Enemy>()->take_damage(1.0f, 15.0f);
		}
	};

	void render(Renderer* ren) override
	{
		ren->draw_circle(pos, 50.0f);
	};
};

namespace Factory {
	void CreateSkillSpinner(Scene* scn, Entity* plr)
	{
		auto ent = scn->create("SkillSpinner");
		ent->add(SkillSpinner(plr));
		ent->add(Collider());
	}
}

