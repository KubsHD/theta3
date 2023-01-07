#include "enemy_adult.h"
#include "collider.h"
#include "gun.h"


Adult::Adult(Player* player_ref) : Enemy(player_ref)
{
	health = 50;
	damage = 10;
	souls = 5;
	money = 3;

	attack_cooldown = 3;
	speed = 1.1f;
	temp_pos = Vec2(0, 0);
	temp_val = 0;
	temp = 0;

	can_walk = true;

	audio_death = Asset::load_sound("audio/adult_death.mp3");
	audio_damage_dealt = Asset::load_sound("audio/adult_damage_dealt.mp3");
}


void Adult::on_death()
{
	if (health <= 0 && is_dead == false)
	{
		// DROP GUN
		Entity* gun =this->entity->world->create("Gun" + entity->name);
		auto gun_collider = gun->add(Collider(Vec2(24, 24), Vec2(0, 0)));
		gun_collider->tag = CollisionTag::Gun;

		auto animator_gun = gun->add(Animator());
		animator_gun->add_animation("anim/gun_shotgun");
		gun->add(Gun(this->entity, player->entity));
		

		// fucking die lmao
		is_dead = true;

		this->death_pos = entity->position;

		if (audio_death != NULL) {
			std::cout << entity->name << " - Zginal : " + std::to_string(entity->position.x)
				+ " / " + std::to_string(entity->position.y) + "\n";

			// play death sound
			Audio::play_one_shot(audio_death);

			// Death Loot Instantly added
			player->health += this->souls;
			player->money += this->money;

			// skasuj przeciwnika		
			this->entity->world->remove(this->entity);


		}
	}
}


void Adult::init()
{
	Enemy::init();

	Vec2 rand_starting_pos;
	// 2 sides of the screen for x
	if (rand() % 2)
	{
		if (rand() % 2)
			rand_starting_pos.x = player->entity->position.x + rand() % 600;
		else
			rand_starting_pos.x = player->entity->position.x - rand() % 600;

		// 2 sides of the screen for y
		if (rand() % 2)
			rand_starting_pos.y = player->entity->position.y + rand() % 200 + 500;
		else
			rand_starting_pos.y = player->entity->position.y - rand() % 200 - 400;
	}
	else
	{
		if (rand() % 2)
			rand_starting_pos.x = player->entity->position.x + rand() % 200 + 800;
		else
			rand_starting_pos.x = player->entity->position.x - rand() % 200 - 700;

		// 2 sides of the screen for y
		if (rand() % 2)
			rand_starting_pos.y = player->entity->position.y + rand() % 400;
		else
			rand_starting_pos.y = player->entity->position.y - rand() % 400;
	}


	entity->position = rand_starting_pos;

	this->entity->get<Animator>()->play_anim("adult_enemy_run");
	this->entity->get<Sprite>()->enabled = false;

	collider = entity->get<Collider>();
	// todo zmienic na rozmiar spritea
	collider->size = this->entity->get<Sprite>()->tex->size;
	collider->tag = CollisionTag::Enemy;

}


void Adult::update()
{
	Enemy::update();

	on_death();

	// Enemies' Sprite center coordinates
	pos_sprite_center = Vec2(entity->position.x + entity->get<Sprite>()->tex->size.x / 2,
		entity->position.y + entity->get<Sprite>()->tex->size.y / 2);

	// Standard
	delta_x = player->pos_sprite_center.x - pos_sprite_center.x;// > 0 ? 1 : -1;
	delta_y = player->pos_sprite_center.y - pos_sprite_center.y;// > 0 ? 1 : -1;
	direction_x = player->pos_sprite_center.x - pos_sprite_center.x > 0 ? 1 : -1;
	direction_y = player->pos_sprite_center.y - pos_sprite_center.y > 0 ? 1 : -1;

	facing_angle = atan2(delta_y, delta_x);

	// Movement 
	if (can_walk)
	{
		if (collider->check_sphere(Vec2(pos_sprite_center.x + cos(facing_angle) * collider->size.x / 8 * 3,
			pos_sprite_center.y + sin(facing_angle) * collider->size.y / 8 * 3), 2, CollisionTag::Enemy))
		{
			// If enemy on the path - move different way

		}
		else if (!collider->check_sphere(Vec2(pos_sprite_center.x + cos(facing_angle) * collider->size.x / 8 * 3,
			pos_sprite_center.y + sin(facing_angle) * collider->size.y / 8 * 3), 2, CollisionTag::Player))
		{
			// If not close enough to player - come closer
			entity->position.x += cos(facing_angle) * speed;
			entity->position.y += sin(facing_angle) * speed;
		}
		else  	
		{
			// If close enough to player - attack this mofo
			if (temp > attack_cooldown * 60)
			{
				// Play attack animation
				// trick do animacji - XDDD
				if (facing_angle > (M_PI / 2) || facing_angle < -(M_PI / 2))
				{
					if (this->entity->position.x > 0)
					{
						delta_x = -10;
						this->entity->get<Animator>()->play_one_shot("adult_enemy_attack", [this]() {});
					}
					else {
						delta_x = 10;
						this->entity->get<Animator>()->play_one_shot("adult_enemy_attack", [this]() {});
					}
				}
				else
				{
					this->entity->get<Animator>()->play_one_shot("adult_enemy_attack", [this]() {});
				}

				// Play attack sound
				Audio::play_one_shot(audio_damage_dealt);

				// Player Damage
				if (player->god_mode == false)
				player->health -= damage;

				// Reset cooldown
				temp = 0;


			}
		}
		//TODO: FIXLATER: IMPORTANT OPTIMIZATION!!!!!!!!!!!! CAN BE MERGED WITH MOVEMENT COLLIDER ABOVE

		// Cooldown countdown
		temp += 1;		

		// 8-way movement
		//entity->position += Vec2(speed * direction_x, speed * direction_y);

	}
}
