#include "scene_shop_test.h"

#include <components/ui/shop/ui_shop_card.h>
#include <components/ui/ui_combo_display.h>

#include <glm/glm.hpp>
#include <core/input.h>

static Vector<UIShopCard*> cards;
static int idx = 0;

void ShopTestScene::init()
{
	target = CreateRef<Target>(1280, 720);

	for (int i = 0; i < 3; i++)
	{
		auto btn = create("shop_card_" + std::to_string(i));
		cards.push_back(btn->add(UIShopCard()));
		
		btn->position = Vec2(400 + 300 * i, 150);
	}

	cards[idx]->selected = true;

	auto c = create("uic");
	c->add(UIComboDisplay());
	c->position = Vec2(0, 600);
}

void ShopTestScene::destroy()
{

}

void ShopTestScene::update()
{
	Scene::update();

	for (auto c : cards)
	{
		c->selected = false;
	}

	if (Input::key_down(SDL_SCANCODE_RIGHT))
	{
		idx++;
	}
	else if (Input::key_down(SDL_SCANCODE_LEFT))
	{
		idx--;
	}

	cards[idx]->selected = true;
}

void ShopTestScene::render()
{
	ren->set_target(target.get());
	ren->clear(Vec3(0.0f, 0.0f, 0.0f));

	Scene::render();

	ren->set_target(Renderer::Backbuffer);
	ren->clear(Vec3(0.0f, 0.0f, 0.0f));

	ren->draw_target(target.get());
}

