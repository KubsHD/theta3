#pragma once

#include <core/types.h>
#include <core/ecs.h>

class Light;

class Flashlight : public Component {

public:
	void init() override;
	void update() override;
	void render(Renderer* ren) override;
	void destroy() override;
private:
	
	Light* m_lightRef;
	float m_flashlightAngle;
};