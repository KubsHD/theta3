#include "scene_game.h"

#include <components/sprite.h>
#include <components/movement.h>
#include <components/animator.h>

// player
#include <components/player.h>

// waves system
#include <components/wave_system.h>

// bullets
#include <components/enemy_bullet.h>


#include <core/log.h>
#include <core/window.h>
#include <core/input.h>
#include <core/types.h>
#include <core/ecs.h>

#include "render/renderer.h"
#include <components/collider.h>
#include <components/effects.h>


void GameScene::init()
{
	// zmiana rozmiaru wymaga zmiany w spawnowaniu przeciwnikow [enemy]::init
	game_view = CreateRef<Target>(960, 540);
	game_camera = CreateRef<Camera>();

	ren->set_camera(game_camera.get());

	//auto bg = create("bg");
	//bg->add(Sprite("data/tmp_map2.png"));

	// Player initialization
	auto player = create("Player");
	player->add(Collider(Vec2(32, 32), Vec2(0, 0)))->tag = CollisionTag::Player;
	player->add(Player());
	//player->add(Sprite("data/spr_player.png"));

	auto animator = player->add(Animator());
	animator->add_animation("data/anim/anm_witch_atk_R");
	animator->add_animation("data/anim/witch_idle");
	animator->add_animation("data/anim/witch_run");
	
	
	player->add(PlayerMovement(2.0f));

	player_ref = player;



	Entity* rain = create("rain");
	//rain->add(Sprite("data/effects_rain.png"));
	auto animator_rain = rain->add(Animator());
	animator_rain->add_animation("data/anim/effects_rain");
	rain->add(Effect(player));


	auto wave = create("WaveManager");
	wave->add(Wave(player));



	



	//// Coin 
	//Entity* money = create("money1");
	//money->add(Sprite("data/coin.png"));
	//auto animator_money = money->add(Animator());
	//animator_money->add_animation("data/anim/coin");
	//money->add(Money(player));

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