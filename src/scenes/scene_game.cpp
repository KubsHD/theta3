#include "scene_game.h"

#include <components/animator.h>
#include <components/collider.h>
#include <components/effects.h>
#include <components/map.h>
#include <components/movement.h>
#include <components/player.h>
#include <components/sprite.h>
#include <components/ui/ui_hp_bar.h>
#include <components/wave_system.h>
#include <components/bullet_manager.h>
#include <components/gun.h>

#include <core/asset.h>
#include <core/audio.h>
#include <core/ecs.h>
#include <core/log.h>
#include <core/input.h>
#include <core/types.h>
#include <core/window.h>

#include "render/renderer.h"
#include <components/ui/ui_coin_display.h>


void GameScene::init()
{
	// zmiana rozmiaru wymaga zmiany w spawnowaniu przeciwnikow [enemy]::init
	game_view = CreateRef<Target>(960, 540);
	game_camera = CreateRef<Camera>();

	ren->set_camera(game_camera.get());

	// Backround Image // TODO: replace with generated tiles maybe
	auto map = create("Map");
	map->add(Sprite("test_map.png"));
	map->add(MapGenerator());


	// Backround Sound
	//Sound* backround_music = Asset::load_sound("audio/background_music_1.mp3");
	//Audio::play_one_shot(backround_music, 0.01f);



	// Player initialization
	auto player = create("Player");
	player->add(Sprite("spr_player.png"));
	player->get<Sprite>()->enabled = false;
	// Forgiving hitboxs for noobs
	Vec2 player_hitbox = Vec2(player->get<Sprite>()->tex->size.x * 2 / 3, player->get<Sprite>()->tex->size.y * 2 / 3);
	Vec2 player_hitbox_offset = Vec2(player->get<Sprite>()->tex->size.x * 2 / 6, player->get<Sprite>()->tex->size.y * 2 / 6);
	player->add(Collider(player_hitbox, player_hitbox_offset))->tag = CollisionTag::Player;
	player->add(Player());

	auto animator = player->add(Animator());

	animator->add_animation("anim/anm_witch_attack_cmb_1");
	animator->add_animation("anim/anm_witch_attack_cmb_2");
	animator->add_animation("anim/anm_witch_attack_cmb_3");

	animator->add_animation("anim/witch_broom_activation");
	animator->add_animation("anim/witch_broom_move");
	animator->add_animation("anim/witch_idle");
	animator->add_animation("anim/witch_run");
	
	
	player->add(PlayerMovement(2.0f));

	player_ref = player;

	// TO MAP
	map->get<MapGenerator>()->player_ref = player;


	Entity* rain = create("rain");
	//rain->add(Sprite("data/effects_rain.png"));
	auto animator_rain = rain->add(Animator());
	animator_rain->add_animation("anim/effects_rain");
	rain->add(Effect(player));


	auto gun_spawner = create("GunSpawner");
	gun_spawner->add(GunSpawner(player));

	auto wave = create("WaveManager");
	wave->add(Wave(player));

	auto bullet_system = create("BulletManager");
	bullet_system->add(BulletManager());


	// prepare ui
	ui = new Entity();
	ui->name = "ui";
	ui->world = this;
	ui->position = Vec2(0, 0);
	
	ui->add(UIHpBar());
	ui->add(UICoinDisplay());


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
	for (auto& c : ui->get_components())
	{
		c->update();
	}
}

void GameScene::render()
{
	ren->set_camera(game_camera.get());
	ren->set_target(game_view.get());
	ren->clear(Vec3(0.03f, 0.4f, 0.03f));

	Scene::render();


	ren->set_camera(nullptr);
	ren->set_target(Renderer::Backbuffer);

	ren->clear(Vec3(0, 0, 0));

	ren->draw_target(game_view.get());

	for (auto& c : ui->get_components())
	{
		c->render(ren);
	}
}

void GameScene::destroy()
{

}