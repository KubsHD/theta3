#pragma once

#include <core/types.h>
#include <core/ecs.h>

class Light;

/// <summary>
/// Flashlight component
/// </summary>
class Flashlight : public Component {

public:
	void init() override;
	void update() override;
	void render(Renderer* ren) override;
	void destroy() override;
private:
	
	/// <summary>
	/// Light reference
	/// </summary>
	Light* m_lightRef;

	/// <summary>
	/// Flashlight's angle
	/// </summary>
	float m_flashlightAngle;
};