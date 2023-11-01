#include "scene_light_test.h"

#include <glm/glm.hpp>
#include <core/input.h>
#include <render/device.h>
#include <core/asset.h>
#include <core/game.h>

#include <components/player.h>
#include <components/movement.h>

static int x = 300;

void LightTestScene::init()
{
	target = gpu::device->create_target({ 640, 360, TargetScalingType::Nearest});
	lit_shader = Asset::load_shader("lit");
	test = Asset::load_texture("coin.png");

	// Player initialization
	auto player = create("Player");
	player->add(Sprite("spr_player.png"));
	player->get<Sprite>()->enabled = false;


	// Forgiving hitboxs for noobs
	Vec2 player_size = Vec2(player->get<Sprite>()->tex->size.x, player->get<Sprite>()->tex->size.y);
	Vec2 player_hitbox = Vec2(player_size.x * 5 / 7, player_size.y * 5 / 7);
	Vec2 player_hitbox_offset = Vec2((player_size.x - player_hitbox.x) / 2, (player_size.y - player_hitbox.y) / 2);
	player->add(Collider(player_hitbox, player_hitbox_offset))->tag = CollisionTag::Player;
	player->add(Player());

	//Factory::CreateSkillSpinner(this, player);

	auto animator = player->add(Animator());

	animator->shader = lit_shader;

	animator->add_animation("anim/anm_witch_attack_cmb_1");
	animator->add_animation("anim/anm_witch_attack_cmb_2");
	animator->add_animation("anim/anm_witch_attack_cmb_3");

	animator->add_animation("anim/witch_broom_activation");
	animator->add_animation("anim/witch_broom_move");
	animator->add_animation("anim/witch_idle");
	animator->add_animation("anim/witch_run");


	player->add(PlayerMovement(player, 2.0f));
}

void LightTestScene::destroy()
{

}

void LightTestScene::update()
{
	Scene::update();

	lit_shader->set_uniform_vec2("u_lightPos", Vec2(x, 200.0f));

	x += 1;
	if (x > 400)
		x = 150;
}

void LightTestScene::render()
{
	ren->set_target(target);
	ren->clear(Vec3(0.0f, 0.0f, 0.0f));

	ren->draw_tex_s(test, Vec2(250.0f, 150.0f), Vec2(100.0f, 100.0f), lit_shader);
	//ren->draw_tex(test, Vec2(x, 200.0f));

	Scene::render();


	ren->set_target(Renderer::Viewport);
	ren->clear(Vec4(0.0f, 0.0f, 0.0f, 1.0f));

	ren->draw_target(target);
}

