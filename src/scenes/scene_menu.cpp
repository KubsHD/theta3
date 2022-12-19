#include "scene_menu.h"

#include <components/ui/ui_button.h>
#include <core/input.h>
#include <core/audio.h>
#include "scene_game.h"
#include <main.h>
#include <core/asset.h>


void MenuScene::init()
{
	font = Asset::load_font("data/font/comic.fnt");
	target = CreateRef<Target>(1280, 720);

	{
		auto btn = create("btn_start");
		auto uib = btn->add(UIButton("Start"));
		
		btn->position = Vec2(100, 500);
		uib->selected = false;
		uib->on_clicked = [this]() {
			change_scene<GameScene>();
		};

		btns.push_back(uib);
	}

	{
		auto btn = create("btn_settings");
		auto uib = btn->add(UIButton("Ustawienia"));

		btn->position = Vec2(100, 550);
		uib->selected = false;

		btns.push_back(uib);
	}

	{
		auto btn = create("btn_quit");
		auto uib = btn->add(UIButton("Wyjscie"));

		btn->position = Vec2(100, 600);
		uib->selected = false;
		uib->on_clicked = [this]() {
		};

		btns.push_back(uib);
	}

	aud = Asset::load_sound("data/ui_1.wav");
}

void MenuScene::destroy()
{
}

void MenuScene::update()
{
	for (auto btn : btns)
		btn->selected = false;

	btns[idx]->selected = true;

	if (Input::key_down(SDL_SCANCODE_DOWN) || Input::key_down(SDL_SCANCODE_S))
	{
		if (idx + 1 < btns.size())
		{
			idx++;
			Audio::play_one_shot(aud);
		}
	}
	else if (Input::key_down(SDL_SCANCODE_UP) || Input::key_down(SDL_SCANCODE_W))
	{
		if (idx - 1 >= 0)
		{
			idx--;
			Audio::play_one_shot(aud);
		}

	}
	else if (Input::key_down(SDL_SCANCODE_SPACE) || Input::key_down(SDL_SCANCODE_RETURN))
	{
		btns[idx]->on_clicked();
	}


}

void MenuScene::render()
{ 
	ren->set_target(target.get());
	ren->clear(Vec3(0.0f, 0.0f, 0.0f));
	ren->draw_text("Theta2", font, Vec2(100, 100));
	ren->draw_circle(Vec2(0, 0), 100);


	Scene::render();

	ren->set_target(Renderer::Backbuffer);
	ren->clear(Vec3(0.0f, 0.0f, 0.0f));

	ren->draw_target(target.get());
}
