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

	bool flip = 0;
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
	int looper, maxloops;
	float lerp_rate;
	Vec2 dot_pos = Vec2(100, 100);
	Vec3 dot_color = Vec3(static_cast <float> (rand()) / static_cast <float> (100) / 100.0f, static_cast <float> (rand()) / static_cast <float> (100) / 100.0f
		, static_cast <float> (rand()) / static_cast <float> (100) / 100.0f);

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

		looper = 0;
		maxloops = 10;

		lerp_rate = 0.024;

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
		if (ImGui::Begin("FollowPlayer settings"))
		{
			ImGui::DragFloat("LerpRate", &lerp_rate, 0.001f, 0.002f, .5f);
		}
		ImGui::End();
		// renderowanie
		//if (is_dead == true) {
		//	ren->draw_text("elooo", Renderer::DefaultFont, text_pos, 0.8, 1);
		//	//text_opacity -= 0.1f;
		//}
		if (!path.empty()) {
			for (size_t i = 1; i < path.size(); ++i) {
				auto& coordinate = path[i];
				dot_pos = { coordinate.x * 20, coordinate.y * 20 };
				//std::cout << "dot: " << dot_pos.x << " " << dot_pos.y << "\n";
				this->entity->world->ren->draw_circle(dot_pos, 5, dot_color);
			}
		}
	}

	/// <summary>
	/// subtracts health from enemy that was hit
	/// </summary>
	/// <param name="melee_damage">damage given</param>
	/// <param name="knockback_rate">knockback multiplier</param>
	/// <param name="facing_angle">angle the enemy is facing</param>
	void take_damage(float melee_damage, float knockback_rate);

	void followPlayer();
};




