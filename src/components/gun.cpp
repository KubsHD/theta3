#include "gun.h"

void GunSpawner::drop_gun(int gun_type)
{
	switch (gun_type)
	{
	case SHOTGUN:
	{
		attack_cooldown = 2.3f * 60;
		magazine_capacity = 4;
		bullets_left = magazine_capacity;
		damage = 21;
		String anim = "gun_shotgun";

		break;
	}
	
	case PISTOL:
		break;
	case MACHINE_GUN:
		break;
	case CROSSBOW:
		break;

	default:
		break;
	}


}



//std::cout << "GUN DROPPED";
//
//Entity* gun = entity->world->create("Gun");
//gun->add(Collider(Vec2(20, 20), Vec2(0, 0)));
//
//auto animator_adult = gun->add(Animator());
//animator_adult->add_animation("anim/gun");
//
//gun->add(GunSpawner());