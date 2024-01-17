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

#include <components/sprite.h>	
#include <core/audio.h>
#include <core/asset.h>
#include <components/player.h>
#include <render/Renderer.h>
#include <components/gun.h>
#include <components/pickups/Inventory.h>
#include <components/text_popup.h>
#include <glm/gtx/compatibility.hpp>

class Player;



/// <summary>
/// class containing all the necessary attributes and methonds shared by enemies
/// </summary>
class Pickupable : public Component
{
public:
	// backend
	float facing_angle, temp, text_opacity = 1;
	
	Collider* collider;
	Vec2 death_pos, text_pos;
	Vec2 pos_sprite_center;
	Player* player;
	Pickupable() = default;

	Pickupable(Player* player_ref) {
		player = player_ref;
	}

	virtual void onPickUp() {

		printf("Non overriden pickup!");
		this->entity->world->remove(this->entity);

	};

	void init() override
	{
		collider = this->entity->get<Collider>();
		//// todo zmienic na rozmiar spritea
		collider->size = Vec2(32, 32);
		collider->tag = CollisionTag::Pickup;
	}



	void update() override;



	void render(Renderer* ren) override
	{
		/*if (ImGui::Begin("Pickup settings"))
		{
			ImGui::DragFloat("Facing angle", &facing_angle, 1.0f, 1.0f, 360.0f);
		}
		ImGui::End();*/

		
	}

};




