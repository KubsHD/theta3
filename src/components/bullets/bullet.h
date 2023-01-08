#pragma once

#include <core/types.h>
#include <render/Renderer.h>
#include <core/ecs.h>
#include <components/collider.h>
#include <components/sprite.h>
#include <components/player.h>


class Bullet : public Component
{
public:
    //static unsigned int bullet_ID;
    float facing_angle, delta_x, delta_y;
    Vec2 starting_pos, destination;
    Collider* collider;
    Gun* gun;
    Player* player;

	float attack_cooldown;
	float damage;
	float bullet_speed;
	int magazine_capacity;
	int bullets_left;

	Sound* shot;
	Sound* on_hit;
	String weapon_sprite;
	String bullet_sprite;


	Bullet() = default;
    Bullet(Entity* player_ref)
    {
        this->player = player_ref->get<Player>();
        destination = Vec2(0, 0);
    }

	~Bullet()
	{
		//Bullet::bullet_ID--;
	}

	void init()
    {
		switch (player->selected_weapon)
		{
		case SHOTGUN:
		{
			attack_cooldown = 1.4f * 60;
			magazine_capacity = 4;
			bullets_left = magazine_capacity;
			damage = 21;
			bullet_speed = 3.4f;
			weapon_sprite = "icon_shotgun.png";
			bullet_sprite = "bullet1.png";

			break;
		}

		case PISTOL:
		{
			attack_cooldown = 0.4f * 60;
			magazine_capacity = 9;
			bullets_left = magazine_capacity;
			damage = 13;
			bullet_speed = 3.4f;
			weapon_sprite = "icon_pistol.png";
			bullet_sprite = "bullet2.png";

			break;
		}

		case MACHINE_GUN:
		{
			attack_cooldown = 0.15f * 60;
			magazine_capacity = 60;
			bullets_left = magazine_capacity;
			damage = 7;
			bullet_speed = 2.4f;
			weapon_sprite = "icon_machine_gun.png";
			bullet_sprite = "bullet3.png";

			break;
		}

		case CROSSBOW:
		{
			attack_cooldown = 2.5f * 60;
			magazine_capacity = 3;
			bullets_left = magazine_capacity;
			damage = 83;
			bullet_speed = 6.4f;
			weapon_sprite = "icon_crossbow.png";
			bullet_sprite = "bullet4.png";

			break;
		}

		default:
			break;
		}

        entity->position = player->entity->position;
        
        // 

        delta_x = player->pos_sprite_center.x - destination.x;
        delta_y = player->pos_sprite_center.y - destination.y;


        facing_angle = atan2(delta_y, delta_x);


        collider = entity->get<Collider>();
        collider->size = this->entity->get<Sprite>()->tex->size;
        collider->tag = CollisionTag::Bullet;
    }

    void update() override
    {
        entity->position.x += cos(facing_angle) * bullet_speed;
        entity->position.y += sin(facing_angle) * bullet_speed;

    }


	void render(Renderer* ren) override
	{

	}

};


namespace Factory {
	void CreateBullet(Scene* scn, Player* pl1ayer);
   
}
