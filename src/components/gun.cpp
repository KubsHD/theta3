#include "gun.h"

void Gun::gun_choose_type(int gun_type)
{
	switch (gun_type)
	{
	case SHOTGUN:
	{
		attack_cooldown = 1.4f * 60;
		magazine_capacity = 4;
		bullets_left = magazine_capacity;
		damage = 21;
		anim = "anim/gun_shotgun";
		sprite = "icon_shotgun.png";

		break;
	}

	case PISTOL:
	{
		attack_cooldown = 0.4f * 60;
		magazine_capacity = 9;
		bullets_left = magazine_capacity;
		damage = 13;
		sprite = "icon_pistol.png";

		break;
	}

	case MACHINE_GUN:
	{
		attack_cooldown = 0.15f * 60;
		magazine_capacity = 60;
		bullets_left = magazine_capacity;
		damage = 7;
		sprite = "icon_machine_gun.png";

		break;
	}

	case CROSSBOW:
	{
		attack_cooldown = 2.5f * 60;
		magazine_capacity = 3;
		bullets_left = magazine_capacity;
		damage = 83;
		sprite = "icon_crossbow.png";

		break;
	}

	default:
		break;
	}
}

void Gun::init()
{
	gun_choose_type(rand() % 4);
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
	ren->draw_tex(Asset::load_texture(sprite), entity->position);
}