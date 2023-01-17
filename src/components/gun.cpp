#include "gun.h"

void Gun::gun_choose_type(int gun_type)
{
	switch (gun_type)
	{
	case PISTOL:
	{
		weapon_sprite = "icon_pistol.png";
		break;
	}

	case SHOTGUN:
	{
		weapon_sprite = "icon_shotgun.png";
		break;
	}

	case MACHINE_GUN:
	{
		weapon_sprite = "icon_machine_gun.png";
		break;
	}

	case CROSSBOW:
	{
		weapon_sprite = "icon_crossbow.png";
		break;
	}
	default:
		break;
	}
}


void Gun::init()
{
	gun_choose_type(rand() % 4 + 1);
	entity->position = enemy->position;
	collider = this->entity->get<Collider>();
	//this->entity->get<Animator>()->play_anim("gun_shotgun");
}


void Gun::update()
{

	if (collider->check_sphere(Vec2(this->entity->position.x + collider->size.x / 2,
		this->entity->position.y + collider->size.y / 2), 20.0f, CollisionTag::Player))
	{
		this->entity->world->remove(this->entity);

	}
}


void Gun::render(Renderer* ren)
{
	ren->draw_tex(Asset::load_texture(weapon_sprite), entity->position);
}