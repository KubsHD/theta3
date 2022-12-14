#include "wave_system.h"

#include <lib/imgui/imgui.h>



Wave::Wave(Entity* player)
{
	this->player = player;
}

void Wave::init()
{
	waveID = 0;
	round_time = 0;
	frames = 0;
}

void Wave::update()
{
	if (frames == 60)
	{
		round_time++;
		frames = 0;
		if (round_time % 5 == 0)
		{
			waveID++;
			wave_spawn();
		}
	}
	frames++;

}

void Wave::render(Renderer* ren)
{
	if (ImGui::Begin("wave info"))
	{
		ImGui::Text("ROUND TIME: %d", round_time);
		ImGui::Text("WAVE: %d", waveID);
		ImGui::End();
	}
}


void Wave::wave_spawn()
{

	for (int i = 0; i < 20; i++)
	{
		Entity* adult = entity->world->create("AdultEnemyW" + std::to_string(waveID) + "E" + std::to_string(i));
		adult->add(Sprite("data/spr_enemy_adult.png"));
		adult->add(Collider(Vec2(32, 32), Vec2(0, 0)));

		auto animator_adult = adult->add(Animator());
		animator_adult->add_animation("data/anim/normal_human_move");

		adult->add(Adult(player->get<Player>()));
	}




	//// Enemy Child
	//Entity* child = entity->world->create("ChildEnemy1");
	//child->add(Child(player));
	//child->add(Sprite("data/spr_enemy_child.png"));

	//auto animator_child = child->add(Animator());

	//// Enemy Policeman
	//Entity* policeman = entity->world->create("PolicemanEnemy1");
	//policeman->add(Policeman(player));
	//policeman->add(Sprite("data/spr_enemy_police.png"));

	//auto animator_policeman = policeman->add(Animator());


	//// Enemy Soldier
	//Entity* soldier = entity->world->create("SoldierEnemy1");
	//soldier->add(Soldier(player));
	//soldier->add(Sprite("data/spr_enemy_soldier.png"));

	//auto animator_soldier = soldier->add(Animator());

	//// Enemy Fatass
	//Entity* fatass = entity->world->create("FatassEnemy1");
	//fatass->add(Fatass(player));
	//fatass->add(Sprite("data/spr_enemy_fatass.png"));

	//auto animator_fatass = fatass->add(Animator());


}