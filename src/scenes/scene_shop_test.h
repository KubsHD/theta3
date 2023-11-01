#pragma once

#include <core/ecs.h>
#include <render/Renderer.h>
#include <core/routine.h>
#include <core/audio.h>


class ShopTestScene : public Scene {
public:
	ShopTestScene() = default;
	~ShopTestScene() {};

	void init() override;



	void destroy() override;


	void update() override;


	void render() override;

	Target* target;

};