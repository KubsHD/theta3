#include "bullet.h"

void Factory::CreateBullet(Scene* scn, Player* player)
{
	String bullet_sprite;
	switch (player->selected_weapon)
	{
	case PISTOL:
	{
		bullet_sprite = "bullet1.png";
		break;
	}
	case SHOTGUN:
	{
		bullet_sprite = "bullet2.png";
		break;
	}
	case MACHINE_GUN:
	{
		bullet_sprite = "bullet3.png";
		break;
	}
	case CROSSBOW:
	{
		bullet_sprite = "bullet4.png";
		break;
	}
	default:
		break;
	}

	auto ent = scn->create("Bullet"); // std::to_string(Bullet::bullet_ID));
	ent->add(Sprite("bullets/" + bullet_sprite));
	ent->add(Collider());
	ent->add(Bullet(player->entity));
	//Bullet::bullet_ID++;
}

void Factory::shotgunShoot(Scene* scn, Player* player)
{
	for (int i = 0; i < rand() % 4 + 3; i++)
	{
		CreateBullet(scn, player);
	}
}
