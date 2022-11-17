#include "scene_menu.h"

#include <render/Renderer.h>

Ref<Font> font;

void MenuScene::init()
{
	font = CreateRef<Font>("data/font/comic.fnt");
}

void MenuScene::destroy()
{

}

void MenuScene::update()
{

}

void MenuScene::render()
{
	ren->set_target(Renderer::Backbuffer);
	ren->draw_text("testowy string", font.get(), Vec2(100, 100));
}
