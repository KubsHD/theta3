#include "light_system.h"

#include <render/Shader.h>

#include <lib/glad/glad.h>

void LightSystem::init()
{
	// generate ubos
	glGenBuffers(1, &m_uboId);
	glBindBuffer(GL_UNIFORM_BUFFER, m_uboId);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(PointLightData) * MAX_POINT_LIGHTS, NULL, GL_DYNAMIC_DRAW); // allocate 152 bytes of memory

	// important
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_uboId, 0, sizeof(PointLightData) * MAX_POINT_LIGHTS);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
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

void LightSystem::prepare_shader(Shader *shd)
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_uboId);

	glUniformBlockBinding(shd->get_id(), glGetUniformBlockIndex(shd->get_id(), "LightData"), 0);
	
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(PointLightData) * MAX_POINT_LIGHTS, m_point_lights);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(PointLightData) * MAX_POINT_LIGHTS, sizeof(SpotLightData) * m_spot_light_count, m_spot_lights);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	shd->set_uniform_float("u_ambientStrength", 0.2);
	
	if (m_point_light_count < MAX_POINT_LIGHTS)
		shd->set_uniform_int("u_pointLightCount", m_point_light_count);
	
	if (m_spot_light_count < MAX_SPOT_LIGHTS)
		shd->set_uniform_int("u_spotLightCount", m_spot_light_count);
}

