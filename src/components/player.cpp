#include "player.h"

#include <render/Renderer.h>
#include <string>
#include <core/log.h>
#include <lib/imgui/imgui.h>


Player::Player()
{
	god_mode = false;
	health = 100;
	speed = 1.0f;
	damage_melee = 10;
	money = 0;
	health_decay = 0.05f;


}

void Player::update()
{
	if(god_mode == false)
		health -= health_decay;
}

void Player::render(Renderer* ren)
{


	if (ImGui::Begin("Player info"))
	{
		ImGui::Text("name: %s", this->entity->name.c_str());
		ImGui::Text("health: %f", this->health);
		ImGui::Text("money: %d", this->money);
		ImGui::Text("speed: %d", this->speed);
		ImGui::Text("health_decay: %f", this->health_decay);
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
