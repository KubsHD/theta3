#include "scene_title.h"

#include <components/ui/ui_button.h>

int title_stage = 0;

//Ref<Texture> fade_tex;


void TitleScene::init()
{
	font2 = CreateRef<Font>("data/font/comic.fnt");
	target = CreateRef<Target>(1280, 720);
	network_prompt = CreateRef<Texture>("data/ui/ui_title_network_prompt.png");
	test = CreateRef<Texture>("data/spr_player.png");

	auto btn_yes = this->create("btn_yes");
	btn_yes->add(UIButton("Tak"));
	btn_yes->position = Vec2(600, 360);

	auto btn_no = this->create("btn_no");
	btn_no->add(UIButton("Nie"));
	btn_no->position = Vec2(600, 440);


}

void TitleScene::destroy()
{
	
}


void TitleScene::update()
{
	Scene::update();

	rt_begin(r);
	{

	}
	rt_while(opacity < 1.0f);
	{
		opacity += 0.01f;
	}
	rt_wait(5.0f);
	{
		rt_while(opacity > 0.1f);
		{
			opacity -= 0.01f;
		}
	}
	rt_end();
}

void TitleScene::render()
{
	ren->set_target(target.get());
	ren->clear(Vec3(0.0f, 0.0f, 0.0f));

	ren->draw_tex(network_prompt.get(), Vec2(0, 0), opacity);
	
	Scene::render();

	ren->set_target(Renderer::Backbuffer);
	ren->clear(Vec3(0.0f, 0.0f, 0.0f));

	ren->draw_target(target.get());
}

