#include "movement.h"

#include <SDL.h>
#include <components/animator.h>
#include <components/sprite.h>
#include <components/collider.h>
#include <components/enemy.h>
#include <core/input.h>
#include <components/gun.h>
#include "particle_system.h"
#include <components/bullets/bullet.h>


enum PLAYER_STATES
{
	IDLE, RUN, ATTACK1, ATTACK2, ATTACK3, ON_BROOM
};


Vector<String> player_anim =
{
	"witch_idle",
	"witch_run",
	"anm_witch_attack_cmb_1",
	"anm_witch_attack_cmb_2",
	"anm_witch_attack_cmb_3",
	"witch_broom_move"
};


PlayerMovement::PlayerMovement(Entity* player_ref, float speed) : speed(speed), is_attacking(false)
{
	player = player_ref->get<Player>();
}

void PlayerMovement::init()
{
	entity->get<Animator>()->play_anim(player_anim[IDLE]);
}


bool in_combo = false;
int combo_step = 1;
int counter = 0;

void PlayerMovement::update()
{
	if (counter > 0)
		counter--;
	else
		combo_step = 1;



	if ((Input::mouse_down(0) || Input::key_down(SDL_SCANCODE_SPACE)) && in_combo == false)
	{
		if (player->selected_weapon == 0) // 0 for BROOM
		{
			is_on_broom = false;
			counter = 60;

			is_attacking = true;
			speed = speed_when_attacking;

			for (auto& i : entity->get<Collider>()->check_sphere_list(entity->position + Vec2(entity->flip ? -5 : 40, 25.0f), 35.0f, CollisionTag::Enemy))
			{

				i->entity->get<Enemy>()->take_damage(melee_damage, knockback_rate);
			}

			switch (combo_step)
			{
			case 1:

				in_combo = true;
				combo_step = 2;

				this->entity->get<Animator>()->play_one_shot(player_anim[ATTACK1], [this]() {
					is_attacking = false;
					speed = speed_base;
					in_combo = false;
					}, 1.5f);
				break;
			case 2:

				combo_step = 3;

				this->entity->get<Animator>()->play_one_shot(player_anim[ATTACK2], [this]() {
					is_attacking = false;
					speed = speed_base;
					in_combo = false;
					}, 1.5f);
				break;
			case 3:

				combo_step = 1;

				this->entity->get<Animator>()->play_one_shot(player_anim[ATTACK3], [this]() {
					is_attacking = false;
					speed = speed_base;
					in_combo = false;
					}, 1.5f);
				break;
			}
		}
		else
		{
			Factory::CreateBullet(entity->world, player);
		}
		
	}

	is_running = false;
	
	if (Input::key_held(SDL_SCANCODE_D)) {
		entity->position.x += speed;
		

		if (!is_attacking)
		{
			this->entity->get<Animator>()->flip = false;
			is_running = true;
			entity->flip = false;
		}
	}

	if (Input::key_held(SDL_SCANCODE_S)) {
		entity->position.y += speed;
		is_running = true;
	}

	if (Input::key_held(SDL_SCANCODE_A)) {
		entity->position.x -= speed;


		if (!is_attacking)
		{
			this->entity->get<Animator>()->flip = true;
			is_running = true;
			entity->flip = true;
		}
	}

	if (Input::key_held(SDL_SCANCODE_W)) {
		entity->position.y -= speed;
		is_running = true;
	}


	if (Input::key_down(SDL_SCANCODE_G) && is_attacking == false) {
		if (is_on_broom)
		{
			is_on_broom = false;
			speed = speed_base;
		}
		else {
			this->entity->get<Animator>()->play_one_shot("witch_broom_activation", []() {});
			speed = speed_on_broom;
			is_on_broom = true;
		}
		
	}

	if (is_running == true )
	{
		if (!is_on_broom)
			this->entity->get<Animator>()->play_anim(player_anim[RUN]);
		else
		{
			ParticleProps pp = {
			.Position = entity->position + Vec2(entity->flip ? 32.0f : 0, 32.0f),
			.LifeTime = 100,
			.Velocity = Vec2((entity->flip ? 1 : -1) * speed * 2, 0.3f),
			.Color = Vec3(0.3f,1.0f,1.0f),
			.Size = Vec2(10.0f ,10.0f),
			.Shape = ParticleShape::Rectangle,
			};

			entity->get<ParticleSystem>()->emit(pp);
			this->entity->get<Animator>()->play_anim(player_anim[ON_BROOM]);
		}
	}
	else if (is_attacking == false && !is_on_broom)
	{
		this->entity->get<Animator>()->play_anim(player_anim[IDLE], 2.0f);
	}
	else if (is_on_broom)
	{


		this->entity->get<Animator>()->play_anim(player_anim[ON_BROOM]);
	}
};


void PlayerMovement::render(Renderer* ren)
{

}

