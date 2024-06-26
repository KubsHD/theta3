
#include "player.h"

#include <render/Renderer.h>
#include <string>
#include <core/log.h>
#include <lib/imgui/imgui.h>
#include <core/input.h>
#include "enemy.h"
#include "components/pickups/Inventory.h"

Player::Player()
{
	isInteracting = false;
	god_mode = false;
	health = 50;
	speed = 1.0f;
	damage_melee = 24;
	money = 0;
	kill_count = 0;
	health_decay = 0.013f; // chujowy gameplay z tym gownem
	selected_weapon = 0;
	weapon_cooldown = 0;
	// in reversed order tho { BROOM, SHOTGUN, PISTOL, MACHINE_GUN, CROSSBOW }
	available_weapons = 0b0000;
	enemies = 0;
}


void Player::init()
{
	Inventory::Init();
	player_offset = Vec2(entity->get<Sprite>()->tex->size.x / 2, entity->get<Sprite>()->tex->size.y / 2);
	entity->position = { 400, 240 };
}

void Player::update()
{
	if(god_mode == false)
		health -= health_decay;

	pos_sprite_center = entity->position + player_offset;

	if (Input::key_down(SDL_SCANCODE_1)){// && (0b0001 & available_weapons))
		if (Inventory::HasAmmo(PISTOL)) {
			selected_weapon = 1;
		}
	}
		

	else if (Input::key_down(SDL_SCANCODE_2))
	{// && (0b0010 & available_weapons))
		if (Inventory::HasAmmo(SHOTGUN)) {
			selected_weapon = 2;

		}
	}
	else if (Input::key_down(SDL_SCANCODE_3))// && (0b0100 & available_weapons))
	{
		if (Inventory::HasAmmo(MACHINE_GUN)) {
			selected_weapon = 3;

		}
	}
	else if (Input::key_down(SDL_SCANCODE_4))// && (0b1000 & available_weapons))
	{
		if (Inventory::HasAmmo(CROSSBOW)) {
			selected_weapon = 4;

		}
	}



	if (Input::key_down(SDL_SCANCODE_E)) {
		isInteracting = true;
	}
	else {
		isInteracting = false;
	}
	if (weapon_cooldown > 0)
		weapon_cooldown--;


	switch (selected_weapon) {
	case PISTOL:
		current_ammo = Inventory::PistolAmmo;
		break;
	case SHOTGUN:
		current_ammo = Inventory::ShotgunAmmo;
		break;
	case MACHINE_GUN:
		current_ammo = Inventory::MachinegunAmmo;
		break;
	case CROSSBOW:
		current_ammo = Inventory::CrossbowAmmo;
		break;
	}

}


void Player::render(Renderer* ren)
{

	if (ImGui::Begin("Player info"))
	{
		ImGui::Text("name: %s", this->entity->name.c_str());
		ImGui::Text("health: %f", this->health);
		ImGui::Text("money: %d", this->money);
		ImGui::Text("speed: %d", this->speed);
		ImGui::Text("cooldown: %d", this->weapon_cooldown);
		ImGui::Text("weaponn: %d", this->selected_weapon);
		ImGui::Text("health_decay: %f", this->health_decay);
		ImGui::Text("pos_sprite_cen: %f, %f", pos_sprite_center.x, pos_sprite_center.y);

		ImGui::Text("god_mode: %d", this->god_mode);

		if (ImGui::Button("god mode"))
		{
			if (god_mode == 0)
				god_mode = 1;
			else
				god_mode = 0;
		}



	}
	ImGui::End();
	
}
