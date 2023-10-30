#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <core/window.h>
#include <core/audio.h>
#include <render/Renderer.h>

#include <components/enemy_adult.h>
#include <components/animator.h>

class UIButton;
class Sound;

enum MenuState {
	Menu,
	Settings,
	NewGame
};

class MenuScene : public Scene {
public:
	MenuScene() {};

	Target* target;

	Font* font;

	MenuState current_state = MenuState::Menu;

	int idx = 0;
	Vector<UIButton*> btns;
	Sound* aud;

	void init() override;


	void destroy() override;


	void update() override;


	void render() override;

};