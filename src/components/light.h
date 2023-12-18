#pragma once

#include <core/types.h>
#include <core/ecs.h>

#include <render/light_system.h>

enum LightType {
	Point,
	Spot
};

class Light : public Component {
	LightSystem* m_lsRef;
	LightHandle m_handle;
public:

	Light(LightSystem* ref, LightType type);
	Light() {};
	~Light();

	LightType type;

	PointLightData point;
	SpotLightData spot;

	void init() override;


	void update() override;


	void render(Renderer* ren) override;

	void destroy() override;
};