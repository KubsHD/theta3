/*****************************************************************//**
 * \file   skill_spinner.h
 * \brief  component responsible for passive spell: spinner 
 * that will rotate around the player and deal damage to enenies knocking them back
 * 
 * \author staniekk
 * \date   January 2023
 *********************************************************************/
#pragma once

#include <core/types.h>
#include <render/Renderer.h>


/// <summary>
/// Class responsible for spinner spell, moving it and displaing
/// </summary>
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
			ent->entity->get<Enemy>()->take_damage(20.0f, .4f, ent->entity->facing_angle);
		}
	};

	void render(Renderer* ren) override
	{
		ren->draw_circle(pos, 50.0f);
	};
};


/// <summary>
/// Helps with creating spells in consise way
/// </summary>
namespace Factory {
	/// <summary>
	/// Creates a ball rotating around the player that deals dmg to enemies
	/// </summary>
	/// <param name="scn">pointer to scene the bullet will be added to</param>
	/// <param name="plr">reference to player</param>
	void CreateSkillSpinner(Scene* scn, Entity* plr)
	{
		auto ent = scn->create("SkillSpinner");
		ent->add(SkillSpinner(plr));
		ent->add(Collider());
	}
}

