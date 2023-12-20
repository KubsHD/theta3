/*****************************************************************//**
 * \file   bullet.h
 * \brief  Component responsible for shooting bullets,
 *  managing stats of different types of bullets,
 *  playing bullets' sounds and deleting them
 * 
 * \date   January 2023
 *********************************************************************/

#include <core/types.h>
#include <render/Renderer.h>
#include <core/ecs.h>
#include <components/collider.h>
#include <components/sprite.h>
#include <components/player.h>
#include <core/input.h>
#include <lib/imgui/imgui.h>
#include <components/gun.h>

#include <components/enemy.h>

/// <summary>
/// Bullet class with all info
/// </summary>
class Bullet : public Component
{
public:
    //static unsigned int bullet_ID;
    float facing_angle, delta_x, delta_y;

	/// <summary>
	/// Entity that was hit by the bullet
	/// </summary>
	Entity entity_hit;

    /// <summary>
	/// Starting position and destination of the bullet
    /// </summary>
    Vec2 starting_pos, destination;
	
    /// <summary>
	/// Collider component
    /// </summary>
    Collider* collider;

    /// <summary>
	/// Gun component
    /// </summary>
    Gun* gun;

    /// <summary>
	/// Player component
    /// </summary>
    Player* player;

	/// <summary>
	/// Attack cooldown, bullet damage, bullet knockback, bullet speed
	/// </summary>
	float attack_cooldown, bullet_damage, bullet_knockback, bullet_speed;
	float auto_destroy_timer = 0;
	int magazine_capacity, bullets_left;
	
	/// <summary>
	/// Sound played when bullet is shot
	/// </summary>
	Sound* audio_shot;

	/// <summary>
	/// Sound played when bullet hits a wall
	/// </summary>
	Sound* adult_damaged;

	/// <summary>
	/// Weapon sprite
	/// </summary>
	String weapon_sprite;

	/// <summary>
	/// Bullet sprite
	/// </summary>
	String bullet_sprite;


	Bullet() = default;
    Bullet(Entity* player_ref)
    {
        this->player = player_ref->get<Player>();
		
		if (player->selected_weapon == SHOTGUN)
		{
			destination = Vec2(Input::get_mouse_pos().x * 3 / 4, Input::get_mouse_pos().y * 3 / 4) - Vec2(480, 270) + Vec2(rand() % 70 - 35, rand() % 70 - 35);
		}
		else if (player->selected_weapon == MACHINE_GUN)
		{
			destination = Vec2(Input::get_mouse_pos().x * 3 / 4, Input::get_mouse_pos().y * 3 / 4) - Vec2(480, 270) + Vec2(rand() % 20 - 10, rand() % 20 - 10);
		}
		else
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
		case PISTOL:
		{
			attack_cooldown = 0.13f * 60;
			magazine_capacity = 9;
			bullets_left = magazine_capacity;
			bullet_damage = 13;
			bullet_knockback = 0.1f;
			bullet_speed = 6.2f;
			weapon_sprite = "icon_pistol.png";
			bullet_sprite = "bullet2.png";
			audio_shot = Asset::load_sound("audio/gun_pistol_shot.mp3");
			break;
		}

		case SHOTGUN:
		{
			attack_cooldown = 0.4f * 60;
			magazine_capacity = 3;
			bullets_left = magazine_capacity;
			bullet_damage = 14;
			bullet_knockback = 0.6f;
			bullet_speed = 6.3f * float(rand() % 12 + 89) / 100.0f;
			weapon_sprite = "icon_shotgun.png";
			bullet_sprite = "bullet1.png";
			audio_shot = Asset::load_sound("audio/gun_shotgun_shot.mp3");
			break;
		}

		case MACHINE_GUN:
		{
			attack_cooldown = 0.05f * 60;
			magazine_capacity = 60;
			bullets_left = magazine_capacity;
			bullet_damage = 9;
			bullet_knockback = 0.04f;
			bullet_speed = 4.6f;
			weapon_sprite = "icon_machine_gun.png";
			bullet_sprite = "bullet3.png";
			audio_shot = Asset::load_sound("audio/gun_machinegun_shot.mp3");

			break;
		}

		case CROSSBOW:
		{
			attack_cooldown = 2.0f * 60;
			magazine_capacity = 3;
			bullets_left = magazine_capacity;
			bullet_damage = 160;
			bullet_knockback = 0.9f;
			bullet_speed = 9.4f;
			weapon_sprite = "icon_crossbow.png";
			bullet_sprite = "bullet4.png";
			audio_shot = Asset::load_sound("audio/gun_crossbow_shot.mp3");

			break;
		}

		default:
			break;
		}

		adult_damaged = Asset::load_sound("audio/adultenemy_damaged.mp3");

        entity->position = player->pos_sprite_center;
        // 

        delta_x = destination.x;
        delta_y = destination.y;


        facing_angle = atan2(delta_y, delta_x);


        collider = entity->get<Collider>();
        collider->size = this->entity->get<Sprite>()->tex->size;
        collider->tag = CollisionTag::Bullet;


		if (audio_shot!= NULL) {
			Audio::play_one_shot(audio_shot, 0.07f);
		}
    }

    void update() override
    {
		auto_destroy_timer++;

        entity->position.x += cos(facing_angle) * bullet_speed;
        entity->position.y += sin(facing_angle) * bullet_speed;

		// TO DO: offset = w init entity->get<Sprite>()->tex->size.x / 2
		if (entity->get<Collider>()->check_sphere(Vec2(entity->position.x + entity->get<Sprite>()->tex->size.x / 2, entity->position.y + entity->get<Sprite>()->tex->size.y / 2), 3.0f, CollisionTag::Enemy, entity_hit))
		{
			entity_hit.get<Enemy>()->take_damage(bullet_damage, bullet_knockback);
			if (audio_shot != NULL) {
				Audio::play_one_shot(adult_damaged, 0.1f);
			}

			this->entity->world->remove(this->entity);
		}


		if (abs(entity->position.x - player->pos_sprite_center.x) > 483)
			this->entity->world->remove(this->entity);
		else if (abs(entity->position.y - player->pos_sprite_center.y) > 273)
			this->entity->world->remove(this->entity);
    }


	void render(Renderer* ren) override
	{

	}

};

/// <summary>
/// Helps with creating bullets in a concise way
/// </summary>
namespace Factory {
	/// <summary>
	/// Creates bullet shot from the player to desired destination
	/// </summary>
	/// <param name="scn">pointer to scene the bullet will be added to</param>
	/// <param name="player">reference to player</param>
	void CreateBullet(Scene* scn, Player* player);
	/// <summary>
	/// Creates bullet burst customized for shotgun
	/// </summary>
	/// <param name="scn">pointer to scene the bullet will be added to</param>
	/// <param name="player">reference to player</param>
	void shotgunShoot(Scene* scn, Player* player);
}
