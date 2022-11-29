#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <render/Renderer.h>

class UIButton;
class Sound;

class MenuScene : public Scene {
public:
	MenuScene() {};

	Ref<Target> target;

	Ref<Font> font;

	int idx = 0;
	Vector<UIButton*> btns;
	Sound* aud;

	void init() override;


	void destroy() override;


	void update() override;


	void render() override;

};