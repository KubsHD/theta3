#include "scene_title.h"

#include <components/ui/ui_button.h>

#include <iostream>
#include <core/input.h>
#include <core/audio.h>
#include <core/asset.h>
#include <components/particle_system.h>

int title_stage = 0;

//Ref<Texture> fade_tex;



void TitleScene::init()
{
	auto a = create("test");
	a->add(ParticleSystem());

	font2 = Asset::load_font("font/comic.fnt");
	target = CreateRef<Target>(1280, 720);
	network_prompt = Asset::load_texture("ui/ui_title_network_prompt.png");
	test = Asset::load_texture("spr_player.png");

	auto btn_yes = this->create("btn_yes");
	{
		auto c = btn_yes->add(UIButton("Tak"));
		c->opacity = 0.0f;
		c->selected = true;
		btns.push_back(c);
	}

	btn_yes->position = Vec2(600, 360);
	

	auto btn_no = this->create("btn_no");

	{
		auto c = btn_no->add(UIButton("Nie"));
		c->opacity = 0.0f;
		c->selected = false;
		btns.push_back(c);
	}

	btn_no->position = Vec2(610, 420);


	aud = Asset::load_sound("ui_1.wav");

}

void TitleScene::destroy()
{
	
}


void TitleScene::update()
{
	Scene::update();

	ParticleProps pp = {
		.Position = get("test")->position,
		.LifeTime = 1.0f,
		.Velocity = Vec2(1.0f, 1.0f),
		.Color = Vec3(0.3f,1.0f,1.0f),
		.Shape = ParticleShape::Rectangle,
	};

	get("test")->get<ParticleSystem>()->emit(pp);

	rt_begin(r);
	rt_while(opacity <= 1.0f);
	{
		opacity += 0.01f;
	}
	rt_step();
	{
		rt_while(get("btn_yes")->get<UIButton>()->opacity <= 1.0f);
		{
			get("btn_yes")->get<UIButton>()->opacity += 0.01f;
			get("btn_no")->get<UIButton>()->opacity += 0.01f;
		}
	}
	rt_end();

	if (get("btn_yes")->get<UIButton>()->opacity >= 1.0f)
	{
		if (Input::key_down(SDL_SCANCODE_DOWN))
		{
			if (idx + 1 < btns.size())
			{
				idx++;
				Audio::play_one_shot(aud);
			}
		}
		else if (Input::key_down(SDL_SCANCODE_UP))
		{
			if (idx - 1 >= 0)
			{
				idx--;
				Audio::play_one_shot(aud);
			}

		}
		else if (Input::key_down(SDL_SCANCODE_SPACE))
		{
			btns[idx]->on_clicked();
		}
	
		for (auto btn : btns)
			btn->selected = false;

		btns[idx]->selected = true;

	}

}

void TitleScene::render()
{
	ren->set_target(target.get());
	ren->clear(Vec3(0.0f, 0.0f, 0.0f));

	ren->draw_tex(network_prompt, Vec2(0, 0), opacity);
	
	Scene::render();

	ren->set_target(Renderer::Backbuffer);
	ren->clear(Vec3(0.0f, 0.0f, 0.0f));

	ren->draw_target(target.get());
}

