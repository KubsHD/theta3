#pragma once

#include <core/ecs.h>
#include <render/Renderer.h>
#include <core/routine.h>
#include <core/audio.h>

class UIButton;

class TitleScene : public Scene {
public:
	TitleScene() = default;
	~TitleScene() {};

	void init() override;



	void destroy() override;


	void update() override;


	void render() override;
	Routine r;

	int idx = 0;
	Vector<UIButton*> btns;

	Texture* network_prompt;
	Texture* test;
	Target* target;
	Font* font2;

	Sound* aud;

	float opacity = 0.0f;
};