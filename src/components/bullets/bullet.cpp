#include "bullet.h"

void Factory::CreateBullet(Scene* scn, Player* player)
{
	String bullet_sprite;
	switch (player->selected_weapon)
	{
	case 1:
	{
		bullet_sprite = "bullet1.png";
		break;
	}
	case 2:
	{
		bullet_sprite = "bullet2.png";
		break;
	}
	case 3:
	{
		bullet_sprite = "bullet3.png";
		break;
	}
	case 4:
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
