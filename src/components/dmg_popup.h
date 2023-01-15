#pragma once 

#include <core/types.h>
#include <core/ecs.h>

class DamagePopup : public Component
{

	float timer;
	float opacity = 1.0f;

	float vel = 1.0f;
public:

	int dmg;
	// Constructors
	DamagePopup() = default;

	// Maintenance
	void update() override
	{
		timer += 1;
		
		entity->position += Vec2(0, -vel);

		if (timer > 50)
			opacity -= 0.01f;

	
	};

	void render(Renderer* ren) override
	{
		ren->draw_text(std::to_string(dmg), Renderer::DefaultFont, entity->position, 1.0f, opacity);
	};
};

namespace Factory {
	void CreateDamagePopup(Scene* scn, Vec2 pos, int amount)
	{
		auto ent = scn->create("dmg");
		auto c = ent->add(DamagePopup());
		ent->position = pos + Vec2(rand() % 10 - 5, 0);
		c->dmg = amount;
	}
}