#pragma once

#include <core/types.h>
#include <core/ecs.h>

class MenuScene : public Scene {
public:
	MenuScene() {};

	void init() override;


	void destroy() override;


	void update() override;


	void render() override;

};