#pragma once

#include <core/types.h>

#define MAX_POINT_LIGHTS 50
#define MAX_SPOT_LIGHTS 50

class Shader;

struct PointLightData {
	alignas(16) Vec2 pos;
	alignas(4) float radius;
	alignas(16) Vec3 color;
};

struct SpotLightData {
	alignas(16) Vec2 pos;
	alignas(16) Vec2 direction;
	alignas(4)  float angle;
	alignas(16) Vec3 color;
};

typedef int LightHandle;

class LightSystem
{
public:
	LightSystem() {};

	void init();
	void update();

	LightHandle add_point_light();
	LightHandle add_spot_light();

	void update_point_light(LightHandle hnd, PointLightData pld);
	void update_spot_light(LightHandle hnd, SpotLightData spotld);

	//void remove_point_light(LightHandle id);
	//void remove_spot_light(LightHandle id);

	void prepare_shader(Shader* m_uberShader);

	float ambient_strength = 0.5f;
private:
	unsigned int m_uboId;

	PointLightData m_point_lights[MAX_SPOT_LIGHTS];
	int m_point_light_count = 0;
	SpotLightData m_spot_lights[MAX_SPOT_LIGHTS];
	int m_spot_light_count = 0;

};