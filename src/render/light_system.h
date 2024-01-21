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

/// <summary>
/// Light system
/// </summary>
class LightSystem
{
public:
	LightSystem() {};

	/// <summary>
	/// Init light system
	/// </summary>
	void init();
	
	
	/// <summary>
	/// Update light system
	///	- Uploads light data to GPU
	/// </summary>
	void update();

	/// <summary>
	/// Request a new point light
	/// </summary>
	/// <returns>Point Light handle</returns>
	LightHandle add_point_light();
	
	/// <summary>
	/// Request a new spot light
	/// </summary>
	/// <returns>Spot Light handle</returns>
	LightHandle add_spot_light();

	/// <summary>
	/// Update point light data to gpu
	/// </summary>
	/// <param name="hnd">Light handle</param>
	/// <param name="pld">Light data struct</param>
	void update_point_light(LightHandle hnd, PointLightData pld);

	/// <summary>
	/// Update spot light data to gpu
	/// </summary>
	/// <param name="hnd">Light handle</param>
	/// <param name="pld">Light data struct</param>
	void update_spot_light(LightHandle hnd, SpotLightData spotld);

	/// <summary>
	/// Remove point light
	/// </summary>
	/// <param name="id">Light handle</param>
	void remove_point_light(LightHandle id);

	/// <summary>
	/// Remove spot light
	/// </summary>
	/// <param name="id">Light handle</param>
	void remove_spot_light(LightHandle id);

	/// <summary>
	/// Prepare shader for rendering
	/// </summary>
	void prepare_shader(Shader* m_uberShader);

	float ambient_strength = 0.5f;
private:

	/// <summary>
	/// Get an available light handle
	/// </summary>
	/// <param name="availability_array">Array</param>
	/// <param name="max_count">Array max count</param>
	/// <returns></returns>
	LightHandle get_available_handle(Vec4* availability_array, int max_count);

	/// <summary>
	/// Free a light handle
	/// </summary>
	/// <param name="hnd">Light handle</param>
	/// <param name="availability_array">Array</param>
	/// <param name="max_count">Array max count</param>
	void free_handle(LightHandle hnd, Vec4* availability_array, int max_count);


	unsigned int m_uboId;

	/// <summary>
	/// Point light data array
	/// </summary>
	PointLightData m_point_lights[MAX_POINT_LIGHTS] = {};
	Vec4 m_point_light_availability[MAX_POINT_LIGHTS] = {};

	/// <summary>
	/// Spot light data array
	/// </summary>
	SpotLightData m_spot_lights[MAX_SPOT_LIGHTS] = {};
	Vec4 m_spot_light_availability[MAX_SPOT_LIGHTS] = {};
};