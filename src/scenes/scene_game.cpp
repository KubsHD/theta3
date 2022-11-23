#include "scene_game.h"

#include <components/sprite.h>
#include <components/movement.h>
#include <components/animator.h>

// enemies
#include <components/enemy_adult.h>
#include <components/enemy_child.h>
#include <components/enemy_policeman.h>
#include <components/enemy_soldier.h>
#include <components/enemy_fatass.h>

// bullets
#include <components/enemy_bullet.h>


#include <core/log.h>
#include <core/window.h>
#include <core/input.h>
#include <core/types.h>
#include <core/ecs.h>

#include "render/renderer.h"

void GameScene::init()
{

	game_view = CreateRef<Target>(800, 450);
	game_camera = CreateRef<Camera>();

	ren->set_camera(game_camera.get());

	auto player = create("Player");
	player->add(Sprite("data/spr_player.png"));
	player->add(PlayerMovement(2.0f));

	auto animator = player->add(Animator());
	animator->add_animation("data/anim/anm_witch_atk_R");


	// Enemy Adult
	Entity* adult = create("AdultEnemy1");
	adult->add(Adult(player));
	adult->add(Sprite("data/spr_enemy_adult.png"));

	auto animator_adult = adult->add(Animator());
	animator_adult->add_animation("data/anim/normal_human_move");
	

	// Enemy Child
	Entity* child = create("ChildEnemy1");
	child->add(Child(player));
	child->add(Sprite("data/spr_enemy_child.png"));

	// Enemy Policeman
	Entity* policeman = create("PolicemanEnemy1");
	policeman->add(Policeman(player));
	policeman->add(Sprite("data/spr_enemy_police.png"));


	// Enemy Soldier
	Entity* soldier = create("SoldierEnemy1");
	soldier->add(Soldier(player));
	soldier->add(Sprite("data/spr_enemy_soldier.png"));


	// Enemy Fatass
	Entity* fatass = create("FatassEnemy1");
	fatass->add(Fatass(player));
	fatass->add(Sprite("data/spr_enemy_fatass.png"));


	// Enemy Bullet
	Entity* bullet = create("Bullet1");
	bullet->add(Bullet(player));
	bullet->add(Sprite("data/spr_enemy_bullet1.png"));
}

void GameScene::update()
{
	Scene::update();

	/*float speed = 1.0f;

	if (Input::key_held(SDL_SCANCODE_RIGHT))
		game_camera->position.x += speed;

	if (Input::key_held(SDL_SCANCODE_DOWN))
		game_camera->position.y += speed;

	if (Input::key_held(SDL_SCANCODE_LEFT))
		game_camera->position.x -= speed;

	if (Input::key_held(SDL_SCANCODE_UP))
		game_camera->position.y -= speed;*/

	//game_camera->position = player_ref->position;

	//if (Input::key_down(SDL_SCANCODE_ESCAPE))
	//	Game::Quit();
}

void GameScene::render()
{
	ren->set_target(game_view.get());
	ren->clear();

	Scene::render();

	ren->set_target(Renderer::Backbuffer);
	ren->clear();

	ren->draw_target(game_view.get());
}

void GameScene::destroy()
{

}