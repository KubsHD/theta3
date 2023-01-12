#pragma once

#include <core/types.h>
#include <render/Renderer.h>
#include <core/ecs.h>
#include <components/collider.h>
#include <components/sprite.h>
#include <components/player.h>
#include <core/input.h>
#include <lib/imgui/imgui.h>



class Bullet : public Component
{
public:
    //static unsigned int bullet_ID;
    float facing_angle, delta_x, delta_y;
	Entity entity_hit;
    Vec2 starting_pos, destination;
    Collider* collider;
    Gun* gun;
    Player* player;

	float attack_cooldown, bullet_damage, bullet_knockback, bullet_speed;
	int magazine_capacity, bullets_left;
	Sound* audio_shot;
	Sound* audio_on_hit;
	String weapon_sprite;
	String bullet_sprite;


	Bullet() = default;
    Bullet(Entity* player_ref)
    {
        this->player = player_ref->get<Player>();
		destination = Vec2(Input::get_mouse_pos().x * 3 / 4, Input::get_mouse_pos().y * 3 / 4) - Vec2(480, 270);
    }

	~Bullet()
	{
		//Bullet::bullet_ID--;
	}

	void init()
    {
		switch (player->selected_weapon)
		{
		case 1:
		{
			attack_cooldown = 1.4f * 60;
			magazine_capacity = 4;
			bullets_left = magazine_capacity;
			bullet_damage = 21;
			bullet_knockback = 0.09f;
			bullet_speed = 6.2f;
			weapon_sprite = "icon_shotgun.png";
			bullet_sprite = "bullet1.png";
			audio_shot = Asset::load_sound("audio/gun_pistol_shot.mp3");
			audio_on_hit = Asset::load_sound("audio/gun_pistol_on_hit.mp3");
			break;
		}

		case 2:
		{
			attack_cooldown = 0.4f * 60;
			magazine_capacity = 9;
			bullets_left = magazine_capacity;
			bullet_damage = 13;
			bullet_knockback = 0.02f;
			bullet_speed = 6.2f;
			weapon_sprite = "icon_pistol.png";
			bullet_sprite = "bullet2.png";
			audio_shot = Asset::load_sound("audio/gun_pistol_shot.mp3");
			audio_on_hit = Asset::load_sound("audio/gun_pistol_on_hit.mp3");

			break;
		}

		case 3:
		{
			attack_cooldown = 0.15f * 60;
			magazine_capacity = 60;
			bullets_left = magazine_capacity;
			bullet_damage = 7;
			bullet_knockback = 0.01f;
			bullet_speed = 4.6f;
			weapon_sprite = "icon_machine_gun.png";
			bullet_sprite = "bullet3.png";
			audio_shot = Asset::load_sound("audio/gun_pistol_on_hit2.mp3");
			audio_on_hit = Asset::load_sound("audio/gun_pistol_on_hit.mp3");

			break;
		}

		case 4:
		{
			attack_cooldown = 2.5f * 60;
			magazine_capacity = 3;
			bullets_left = magazine_capacity;
			bullet_damage = 83;
			bullet_knockback = 0.2f;
			bullet_speed = 8.4f;
			weapon_sprite = "icon_crossbow.png";
			bullet_sprite = "bullet4.png";
			audio_shot = Asset::load_sound("audio/gun_pistol_shot.mp3");
			audio_on_hit = Asset::load_sound("audio/gun_pistol_on_hit.mp3");

			break;
		}

		default:
			break;
		}

        entity->position = player->pos_sprite_center;
        // 

        delta_x = destination.x;
        delta_y = destination.y;


        facing_angle = atan2(delta_y, delta_x);


        collider = entity->get<Collider>();
        collider->size = this->entity->get<Sprite>()->tex->size;
        collider->tag = CollisionTag::Bullet;


		if (audio_shot!= NULL) {
			Audio::play_one_shot(audio_shot, 0.05f);
		}
    }

    void update() override
    {
        entity->position.x += cos(facing_angle) * bullet_speed;
        entity->position.y += sin(facing_angle) * bullet_speed;

		// TO DO: offset = w init entity->get<Sprite>()->tex->size.x / 2
		if (entity->get<Collider>()->check_sphere(Vec2(entity->position.x + entity->get<Sprite>()->tex->size.x / 2, entity->position.y + entity->get<Sprite>()->tex->size.y / 2), 3.0f, CollisionTag::Enemy, entity_hit))
		{
			entity_hit.get<Enemy>()->take_damage(bullet_damage, bullet_knockback);
			if (audio_shot != NULL) {
				Audio::play_one_shot(audio_on_hit, 0.05f);
			}

			this->entity->world->remove(this->entity);
		}

    }


	void render(Renderer* ren) override
	{

	}

};


namespace Factory {
	void CreateBullet(Scene* scn, Player* pl1ayer);
   
}
