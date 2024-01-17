#pragma once

#include <core/types.h>

#define MAX_POINT_LIGHTS 100
#define MAX_SPOT_LIGHTS 100

class Shader;

struct PointLightData {
	alignas(16) Vec2 pos;
	alignas(4) float radius;
	alignas(16) Vec3 color;
};

struct SpotLightData {
	alignas(16) Vec2 pos;
	alignas(4)  float angle;
	alignas(4)  float radius;
	alignas(4)  float width;
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

	void remove_point_light(LightHandle id);
	void remove_spot_light(LightHandle id);

	void prepare_shader(Shader* m_uberShader);

	float ambient_strength = 0.5f;
private:

	LightHandle get_available_handle(Vec4* availability_array, int max_count);
	void free_handle(LightHandle hnd, Vec4* availability_array, int max_count);


	unsigned int m_uboId;

	PointLightData m_point_lights[MAX_POINT_LIGHTS] = {};
	Vec4 m_point_light_availability[MAX_POINT_LIGHTS] = {};

	SpotLightData m_spot_lights[MAX_SPOT_LIGHTS] = {};
	Vec4 m_spot_light_availability[MAX_SPOT_LIGHTS] = {};
};