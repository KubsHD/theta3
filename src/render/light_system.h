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

	LightHandle add_point_light();
	LightHandle add_spot_light();

	void update_point_light(LightHandle hnd, PointLightData pld);
	void update_spot_light(LightHandle hnd, SpotLightData spotld);

	//void remove_point_light(LightHandle id);
	//void remove_spot_light(LightHandle id);

	void prepare_shader(Shader* m_uberShader);

	float ambient_strength = 0.5f;
private:
	PointLightData m_point_lights[MAX_SPOT_LIGHTS];
	int m_point_light_count;
	SpotLightData m_spot_lights[MAX_SPOT_LIGHTS];
	int m_spot_light_count;

};