#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <render/Renderer.h>

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

	Ref<Target> target;

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