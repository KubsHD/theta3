#include "gun.h"

void Gun::gun_choose_type(int gun_type)
{
	switch (gun_type)
	{
	case SHOTGUN:
	{
		attack_cooldown = 2.3f * 60;
		magazine_capacity = 4;
		bullets_left = magazine_capacity;
		damage = 21;
		String anim = "anim/gun_shotgun";

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
