#pragma once

#include <core/types.h>
#include <core/ecs.h>

class Target;
class Camera;

class GameScene : public Scene {
	Target* game_view;
	Ref<Camera> game_camera;


public:
	void init() override;
	void update() override;
	void render() override;
	void destroy() override;

};