#pragma once

#include <core/ecs.h>
#include <render/Renderer.h>
#include <core/routine.h>

class TitleScene : public Scene {
public:
	TitleScene() = default;
	~TitleScene() {};

	void init() override;



	void destroy() override;


	void update() override;


	void render() override;
	Routine r;


	Ref<Texture> network_prompt;
	Ref<Texture> test;
	Ref<Target> target;
	Ref<Font> font2;

	float opacity = 0.0f;
};