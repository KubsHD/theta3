#include "scene_light_test.h"

#include <core/types.h>

#include <core/input.h>

#include <render/device.h>
#include <core/asset.h>
#include <core/game.h>

#include <components/sprite.h>
#include <components/player.h>
#include <components/movement.h>
#include <components/collider.h>
#include <components/animator.h>

static Vec2 pos = Vec2(294, 159.0f);

static Target* occluder_map;
static Target* light_map;

static Camera cam;

void LightTestScene::init()
{
	target = gpu::device->create_target({ 640, 360, TargetScalingType::Nearest});
	occluder_map = gpu::device->create_target({ 1024,1024, TargetScalingType::Nearest });
	light_map = gpu::device->create_target({ 256,1, TargetScalingType::Nearest });

	lit_shader = Asset::load_shader("lit");
	test = Asset::load_texture("lamp.png");

	// Player initialization
	auto player = create("Player");
	player->add(Sprite("spr_player.png"));
	player->get<Sprite>()->enabled = false;

	

	Vec2 player_size = Vec2(player->get<Sprite>()->tex->size.x, player->get<Sprite>()->tex->size.y);
	Vec2 player_hitbox = Vec2(player_size.x * 5 / 7, player_size.y * 5 / 7);
	Vec2 player_hitbox_offset = Vec2((player_size.x - player_hitbox.x) / 2, (player_size.y - player_hitbox.y) / 2);
	player->add(Collider(player_hitbox, player_hitbox_offset))->tag = CollisionTag::Player;
	player->add(Player());


	auto animator = player->add(Animator());

	animator->shader = lit_shader;

	animator->add_animation("anim/anm_witch_attack_cmb_1");
	animator->add_animation("anim/anm_witch_attack_cmb_2");
	animator->add_animation("anim/anm_witch_attack_cmb_3");

	animator->add_animation("anim/witch_broom_activation");
	animator->add_animation("anim/witch_broom_move");
	animator->add_animation("anim/witch_idle");
	animator->add_animation("anim/witch_run");


	auto mvm = player->add(PlayerMovement(player, 2.0f));
	player->position = Vec2(420, 260);
	
}

void LightTestScene::destroy()
{

}

void LightTestScene::update()
{
	Scene::update();

	lit_shader->set_uniform_vec2("u_lightPos", pos);
	lit_shader->set_uniform_vec2("u_lightDirection", Vec2(0.0f, -100.0f));
	lit_shader->set_uniform_float("u_lightAngle", 70.0f);

	//x += 1;
	//if (x > 400)
	//	x = 150;
}

void LightTestScene::render()
{
	{
		// draw world from light perspective to occluder map
		ren->set_target(occluder_map);
		ren->clear({ 0.0f, 0.0f, 0.0f, 1.0f });

		cam.position = Vec2(pos.x - occluder_map->target_size.x / 2 + 16,
			pos.y - occluder_map->target_size.y / 2 + 16);

		ren->set_camera(&cam);

		ren->draw_tex_s(test, Vec2(250.0f, 150.0f), Vec2(100.0f, 100.0f), lit_shader);
		//ren->draw_tex(test, Vec2(x, 200.0f));
	}

	{
		ren->set_target(light_map);
		ren->clear({ 0.0f, 0.0f, 0.0f, 0.0f });

		cam.position = Vec2(pos.x - occluder_map->target_size.x / 2 + 16,
			pos.y - occluder_map->target_size.y / 2 + 16);

		ren->set_camera(&cam);
		
	}


	{
		// draw final image
		ren->set_target(target);
		ren->clear(Vec3(0.0f, 0.0f, 0.0f));
		ren->set_camera(nullptr);

		ren->draw_tex_s(test, Vec2(250.0f, 150.0f), Vec2(100.0f, 100.0f), lit_shader);
		//ren->draw_tex(test, Vec2(x, 200.0f));
	}


	Scene::render();

	if (ImGui::Begin("Light"))
	{
		
		ImGui::DragFloat2("light pos", glm::value_ptr(pos));
		
		ImGui::Text("Light view");
		ImGui::Image((void*)occluder_map->texId, ImVec2(256, 256));

		
		ImGui::End();
	}

	ren->set_target(Renderer::Viewport);

	
	ren->clear(Vec4(0.0f, 0.0f, 0.0f, 1.0f));

	ren->draw_target(target);
}

