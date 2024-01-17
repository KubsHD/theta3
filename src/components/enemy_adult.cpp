#include "enemy_adult.h"
#include "collider.h"
#include "gun.h"
#include <components/light.h>


Adult::Adult(Player* player_ref) : Enemy(player_ref)
{
	health = 35 + rand()%150;
	max_health = health;
	damage = 4;
	souls = 5;
	money = 3;

	attack_cooldown_seconds = 3;
	speed = 2.0f;
	temp_pos = Vec2(0, 0);
	temp_val = 0;
	temp = 0;

	can_walk = true;

	audio_death = Asset::load_sound("audio/adult_death.mp3");
	audio_damage_dealt = Asset::load_sound("audio/adult_damage_dealt.mp3");

	Enemy::state = EnemyState::ATTACK;
}


void Adult::on_death()
{
	if (health <= 0 && is_dead == false)
	{
		// DROP GUN
		/*
		if (rand() % 6 == 0)
		{
			Entity* gun = this->entity->world->create("Gun");
			auto gun_collider = gun->add(Collider(Vec2(24, 24), Vec2(0, 0)));
			gun_collider->tag = CollisionTag::Gun;

			auto animator_gun = gun->add(Animator());
			animator_gun->add_animation("anim/gun_shotgun");
			gun->add(Gun(this->entity, player->entity));
		}
		*/

		Entity* pickup = PickupManager::GetRandomPickup(player);
			
		if (pickup) {
			pickup->position = entity->position;
		}
		// fucking die lmao
		is_dead = true;

		this->death_pos = entity->position;

		if (audio_death != NULL) {
			//std::cout << entity->name << " - Zginal : " + std::to_string(entity->position.x)
				//+ " / " + std::to_string(entity->position.y) + "\n";

			// play death sound
			//Audio::play_one_shot(audio_death);
		}

		player->health += this->souls;
		player->money += this->money;

		player->kill_count++;

		// skasuj przeciwnika		
		this->entity->world->remove(this->entity);
	}
}


void Adult::init()
{

	Vec2 rand_starting_pos;
	 //2 sides of the screen for x
	if (rand() % 2)
	{
		if (rand() % 2)
			rand_starting_pos.x = player->entity->position.x + rand() % 230;
		else
			rand_starting_pos.x = player->entity->position.x - rand() % 230;

		// 2 sides of the screen for y
		if (rand() % 2)
			rand_starting_pos.y = player->entity->position.y + rand() % 230 + 230;
		else
			rand_starting_pos.y = player->entity->position.y - rand() % 230 - 230;
	}
	else
	{
		if (rand() % 2)
			rand_starting_pos.x = player->entity->position.x + rand() % 230 + 230;
		else
			rand_starting_pos.x = player->entity->position.x - rand() % 230 - 230;

		// 2 sides of the screen for y
		if (rand() % 2)
			rand_starting_pos.y = player->entity->position.y + rand() % 230;
		else
			rand_starting_pos.y = player->entity->position.y - rand() % 230;
	}




	//entity->position = {player->pos_sprite_center.x + rand() % 200 - 100, player->pos_sprite_center.y + rand() % 200 - 100 };
	entity->position = rand_starting_pos;

	this->entity->get<Animator>()->play_anim("adult_enemy_run");
	this->entity->get<Sprite>()->enabled = false;

	collider = entity->get<Collider>();
	// todo zmienic na rozmiar spritea
	collider->size = this->entity->get<Sprite>()->tex->size;
	collider->tag = CollisionTag::Enemy;

	// temporary turned off
	/*auto l = entity->add(Light(entity->world->ren->light, LightType::Point));
	l->point.color = Vec3(0.4, 0.05, 0.05);
	l->point.radius = 50.0f;*/

	Enemy::init();
}


void Adult::update()
{
	Enemy::handleEnemyMovement();

	Enemy::update();

	on_death();

	if (can_walk)
	{
		Vec2 collider_position = Vec2(entity->position.x + 11 + cos(facing_angle) * collider->size.x / 8 * 3,
			entity->position.y + 15 + sin(facing_angle) * collider->size.y / 8 * 3);

		temp += 1;
		if (collider->check_sphere(collider_position, 2, CollisionTag::Player)) {
			if (temp > attack_cooldown_seconds * 60)
			{
				// Play attack animation
				if (delta_x < 8 || delta_y < 8)
				{
					this->entity->get<Animator>()->play_one_shot("adult_enemy_attack", [this]() {});
				}

				// Play attack sound
				Audio::play_one_shot(audio_damage_dealt, 0.2);

				// Player Damage
				if (player->god_mode == false)
					player->health -= damage;

				// Reset cooldown
				temp = 0;
			}
		}

	}


	//float light_amp = (health + 1 - 70) / (max_health - 70);
	//entity->get<Light>()->point.color = Vec3(light_amp * 1, 0.1, 0.1);
	//
	/*if (state == EnemyState::IN_KNOCKBACK)
		return;*/

		// Enemies' Sprite center coordinates
		/*pos_sprite_center = Vec2(entity->position.x + entity->get<Sprite>()->tex->size.x / 2,
			entity->position.y + entity->get<Sprite>()->tex->size.y / 2d;*/

			//// Standard
	//delta_x = player->pos_sprite_center.x - pos_sprite_center.x;// > 0 ? 1 : -1;
	//delta_y = player->pos_sprite_center.y - pos_sprite_center.y;// > 0 ? 1 : -1;
	//direction_x = player->pos_sprite_center.x - pos_sprite_center.x > 0 ? 1 : -1;
	//direction_y = player->pos_sprite_center.y - pos_sprite_center.y > 0 ? 1 : -1;

	//facing_angle = atan2(delta_y, delta_x);
	//entity->facing_angle = facing_angle;

	//// Movement 
	//if (can_walk)
	//{

	//	
	//	{
	//		// If close enough to player - attack this mofo
			
	//	}


		// TODO: FIXLATER: IMPORTANT OPTIMIZATION!!!!!!!!!!!! CAN BE MERGED WITH MOVEMENT COLLIDER ABOVE

		 //Cooldown countdown
		
	//}
}
