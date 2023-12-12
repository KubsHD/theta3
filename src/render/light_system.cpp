#include "light_system.h"

#include <render/Shader.h>

void LightSystem::init(Shader &uber_shader)
{
}

void LightSystem::update()
{
}

LightHandle LightSystem::add_point_light()
{
	auto light_handle = m_point_light_count;
	m_point_light_count++;

    return light_handle;
}

LightHandle LightSystem::add_spot_light()
{
   	auto spot_handle = m_spot_light_count;
	m_spot_light_count++;

    return spot_handle;
}

void LightSystem::update_point_light(LightHandle hnd, PointLightData pld)
{
	m_point_lights[hnd] = pld;
}

void LightSystem::update_spot_light(LightHandle hnd, SpotLightData spotld)
{
	m_spot_lights[hnd] = spotld;
}

void LightSystem::prepare_shader(Shader *m_uberShader)
{
	if (m_point_light_count == 0)
		return;

	m_uberShader->set_uniform_float("u_ambientStrength", 0.2);
	m_uberShader->set_uniform_vec2("u_pointLights[0].pos", m_point_lights[0].pos);
	m_uberShader->set_uniform_float("u_pointLights[0].radius", m_point_lights[0].radius);
	m_uberShader->set_uniform_vec3("u_pointLights[0].color", m_point_lights[0].color);


	m_uberShader->set_uniform_float("u_pointLightCount", m_point_light_count);
	m_uberShader->set_uniform_float("u_spotLightCount", m_spot_light_count);
}

