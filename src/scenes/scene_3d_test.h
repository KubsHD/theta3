#pragma once

#include <core/ecs.h>
#include <render/Renderer.h>
#include <core/routine.h>
#include <core/audio.h>


class Test3DScene : public Scene {
public:
	Test3DScene() = default;
	~Test3DScene() {};

	void init() override;



	void destroy() override;


	void update() override;


	void render() override;

	Target* target;

};