#include "scene_game.h"

#include <components/sprite.h>
#include <components/movement.h>
#include <components/animator.h>

// player
#include <components/player.h>

// enemies
#include <components/enemy_adult.h>
#include <components/enemy_child.h>
#include <components/enemy_policeman.h>
#include <components/enemy_soldier.h>
#include <components/enemy_fatass.h>

// bullets
#include <components/enemy_bullet.h>


// Coins
#include <components/money.h>

#include <core/log.h>
#include <core/window.h>
#include <core/input.h>
#include <core/types.h>
#include <core/ecs.h>

#include "render/renderer.h"
#include <scenes/map.h>
#include <components/collider.h>


void GameScene::init()
{

	game_view = CreateRef<Target>(960, 540);
	game_camera = CreateRef<Camera>();

	ren->set_camera(game_camera.get());

	//auto bg = create("bg");
	//bg->add(Sprite("data/tmp_map2.png"));

	// Player initialization
	auto player = create("Player");
	player->add(Player());
	player->add(Collider(Vec2(32,32), Vec2(0,0)));
	//player->add(Sprite("data/spr_player.png"));

	auto animator = player->add(Animator());
	animator->add_animation("data/anim/anm_witch_atk_R");
	animator->add_animation("data/anim/witch_idle");
	animator->add_animation("data/anim/witch_run");
	
	
	player->add(PlayerMovement(2.0f));

	player_ref = player;

	// Enemy Adult
	Entity* adult = create("AdultEnemy1");
	adult->add(Sprite("data/spr_enemy_adult.png"));
	adult->add(Collider(Vec2(32, 32), Vec2(0, 0)));

	auto animator_adult = adult->add(Animator());
	animator_adult->add_animation("data/anim/normal_human_move");

	adult->add(Adult(player));


	// Enemy Child
	Entity* child = create("ChildEnemy1");
	child->add(Child(player));
	child->add(Sprite("data/spr_enemy_child.png"));

	auto animator_child = child->add(Animator());

	// Enemy Policeman
	Entity* policeman = create("PolicemanEnemy1");
	policeman->add(Policeman(player));
	policeman->add(Sprite("data/spr_enemy_police.png"));

	auto animator_policeman = policeman->add(Animator());


	// Enemy Soldier
	Entity* soldier = create("SoldierEnemy1");
	soldier->add(Soldier(player));
	soldier->add(Sprite("data/spr_enemy_soldier.png"));

	auto animator_soldier = soldier->add(Animator());

	// Enemy Fatass
	Entity* fatass = create("FatassEnemy1");
	fatass->add(Fatass(player));
	fatass->add(Sprite("data/spr_enemy_fatass.png"));

	auto animator_fatass= fatass->add(Animator());


	// Enemy Bullet
	Entity* bullet = create("Bullet1");
	bullet->add(Bullet(player));
	bullet->add(Sprite("data/spr_enemy_bullet1.png"));

	auto animator_bullet= bullet->add(Animator());


	// Coin 
	Entity* money = create("money1");
	money->add(Sprite("data/coin.png"));
	auto animator_money = money->add(Animator());
	animator_money->add_animation("data/anim/coin");
	money->add(Money(player));

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

	// Player in center of the screen
	game_camera->position = Vec2(player_ref->position.x - game_view->target_size.x / 2 + 16,
							player_ref->position.y - game_view->target_size.y / 2 + 16);

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