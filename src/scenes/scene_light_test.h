#pragma once

#include <core/ecs.h>
#include <render/Renderer.h>
#include <core/routine.h>
#include <core/audio.h>


class LightTestScene : public Scene {
public:
	LightTestScene() {};
	~LightTestScene() {};

	void init() override;


	void destroy() override;


	void update() override;


	void render() override;

	Target* target;
	Texture* test;
	Shader* lit_shader;
};