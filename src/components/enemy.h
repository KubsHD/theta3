/*****************************************************************//**
 * \file   enemy.h
 * \brief  component that makes base for all the types of enemies
 * 
 * \date   January 2023
 *********************************************************************/
#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <stdlib.h>
#include <SDL_stdinc.h>

#include <components/animator.h>
#include <components/sprite.h>	
#include <core/audio.h>
#include <core/asset.h>
#include <components/player.h>
#include <render/Renderer.h>
#include <components/gun.h>
#include "lib/a-star-master/AStar.hpp"

#include <glm/gtx/compatibility.hpp>

class Player;


/// <summary>
/// enum containing all the possible states of the enemy
/// </summary>
enum class EnemyState {
	ATTACK,
	IN_KNOCKBACK
};


/// <summary>
/// class containing all the necessary attributes and methonds shared by enemies
/// </summary>
class Enemy : public Component
{	
public:
	// backend
	float facing_angle, temp, text_opacity = 1;
	int attack_cooldown;

	// Audio
	Sound* audio_death;
	Sound* audio_damage_dealt;
	Sound* audio_damage_recived;

	EnemyState state = EnemyState::ATTACK;

	Collider* collider;
	Vec2 death_pos, text_pos;
	Vec2 pos_sprite_center;
	Player* player;
	bool is_dead = false;
	Vec2 target_knochback_position;

	// movement
	float delta_x, delta_y;
	int direction_x, direction_y;
	AStar::Generator astar;

	AStar::CoordinateList::iterator currentPathPosition;
	AStar::CoordinateList path;

	Vec2 target_pos = { 0, 0 };


	// gameplay
	float health, damage, souls, speed, money;

	Enemy() = default;
	Enemy(Player* player_ref)
	{
		astar.setHeuristic(AStar::Heuristic::euclidean);
		astar.setDiagonalMovement(true);

		player = player_ref;
	}

	void init() override
	{
		astar.setWorldSize({ 48, 27 });
		// You can use a few heuristics : manhattan, euclidean or octagonal.
		astar.setHeuristic(AStar::Heuristic::euclidean);
		astar.setDiagonalMovement(true);

		path = astar.findPath({ static_cast<int>(entity->position.x / 20), static_cast<int>(entity->position.y) / 20 },
			{ int(player->pos_sprite_center.x) / 20, int(player->pos_sprite_center.y) / 20 });
		std::reverse(path.begin(), path.end());


		currentPathPosition = path.begin();

		//collider = entity->get<Collider>();
		//// todo zmienic na rozmiar spritea
		//collider->size = Vec2(32, 32);
		//collider->tag = CollisionTag::Enemy;
	}

	/// <summary>
	/// flips sprite so enemy faces the player
	/// </summary>
	void flip_sprite();

	//void on_death();
	
	//void handle_collision();

	void update() override;

	void render(Renderer* ren) override
	{
		// renderowanie
		//if (is_dead == true) {
		//	ren->draw_text("elooo", Renderer::DefaultFont, text_pos, 0.8, 1);
		//	//text_opacity -= 0.1f;
		//}
	}

	/// <summary>
	/// subtracts health from enemy that was hit
	/// </summary>
	/// <param name="melee_damage">damage given</param>
	/// <param name="knockback_rate">knockback multiplier</param>
	/// <param name="facing_angle">angle the enemy is facing</param>
	void take_damage(float melee_damage, float knockback_rate, float facing_angle);

	void followPlayer();
};




