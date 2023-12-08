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

class LightSystem
{
public:
	LightSystem();
	~LightSystem();

	void init(Shader& uber_shader);
	void update();

	void add_point_light(Vec2 pos, float radius, Vec3 color);
	void add_spot_light(Vec2 pos, Vec2 direction, float angle, Vec3 color);
	
private:
	PointLight m_pointLights[MAX_SPOT_LIGHTS];
	SpotLight m_spotLights[MAX_SPOT_LIGHTS];
}