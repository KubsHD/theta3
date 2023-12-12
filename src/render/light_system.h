#pragma once

#include <core/types.h>

#define MAX_POINT_LIGHTS 50
#define MAX_SPOT_LIGHTS 50

class Shader;

struct PointLightData {
	Vec2 pos;
	float radius;
	Vec3 color;
};

struct SpotLightData {
	Vec2 pos;
	Vec2 direction;
	float angle;
	Vec3 color;
};

typedef int LightHandle;

class LightSystem
{
public:
	LightSystem() {};

	void init(Shader& uber_shader);
	void update();

	LightHandle add_point_light(PointLightData point);
	LightHandle add_spot_light(SpotLightData spot);

	void remove_point_light(LightHandle id);
	void remove_spot_light(LightHandle id);

	void prepare_shader(Shader* m_uberShader);

	float ambient_strength = 0.5f;
private:
	PointLightData m_pointLights[MAX_SPOT_LIGHTS];
	SpotLightData m_spotLights[MAX_SPOT_LIGHTS];
};