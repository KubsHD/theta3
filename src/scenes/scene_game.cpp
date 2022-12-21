#include "scene_game.h"

#include <components/sprite.h>
#include <components/movement.h>
#include <components/animator.h>
#include <components/collider.h>
#include <components/effects.h>
#include <components/wave_system.h>
#include <components/player.h>
#include <components/animator.h>


#include <core/log.h>
#include <core/window.h>
#include <core/input.h>
#include <core/types.h>
#include <core/ecs.h>
#include <core/audio.h>
#include <core/asset.h>

#include "render/renderer.h"


void GameScene::init()
{
	// zmiana rozmiaru wymaga zmiany w spawnowaniu przeciwnikow [enemy]::init
	game_view = CreateRef<Target>(960, 540);
	game_camera = CreateRef<Camera>();

	ren->set_camera(game_camera.get());

	// Backround Image // TODO: replace with generated tiles maybe
	auto background_image = create("bg");
	background_image->add(Sprite("data/tmp_map2.png"));


	// Backround Sound
	Sound* backround_music = Asset::load_sound("data/audio/sad.mp3");
	Audio::play_one_shot(backround_music);



	// Player initialization
	auto player = create("Player");
	player->add(Sprite("data/spr_player.png"));
	player->get<Sprite>()->enabled = false;
	// Forgetting hitboxs for noobs
	Vec2 player_hitbox = Vec2(player->get<Sprite>()->tex->size.x * 2 / 3, player->get<Sprite>()->tex->size.y * 2 / 3);
	Vec2 player_hitbox_offset = Vec2(player->get<Sprite>()->tex->size.x * 2 / 6, player->get<Sprite>()->tex->size.y * 2 / 6);
	player->add(Collider(player_hitbox, player_hitbox_offset))->tag = CollisionTag::Player;
	player->add(Player());

	auto animator = player->add(Animator());
	animator->add_animation("data/anim/anm_witch_atk_R");
	animator->add_animation("data/anim/witch_broom_activation");
	animator->add_animation("data/anim/witch_broom_move");
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