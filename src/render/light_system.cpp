#include "light_system.h"

#include <render/Shader.h>

#include <lib/glad/glad.h>
#include <core/log.h>
#include <core/types.h>

void LightSystem::init()
{
	// generate ubos
	glGenBuffers(1, &m_uboId);
	glBindBuffer(GL_UNIFORM_BUFFER, m_uboId);
	
	const int pld_size = sizeof(PointLightData);
	const int sld_size = sizeof(SpotLightData);


	glBufferData(GL_UNIFORM_BUFFER, pld_size * MAX_POINT_LIGHTS + sld_size * MAX_SPOT_LIGHTS + sizeof(Vec4) * MAX_POINT_LIGHTS + sizeof(Vec4) * MAX_SPOT_LIGHTS, NULL, GL_DYNAMIC_DRAW);

	// important
	//glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_uboId, 0, sizeof(PointLightData) * MAX_POINT_LIGHTS + sizeof(SpotLightData) * MAX_SPOT_LIGHTS + sizeof(int) * MAX_POINT_LIGHTS + sizeof(int) * MAX_SPOT_LIGHTS);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_uboId);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	// set default values
	for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
		m_spot_light_availability[i].x = 0;
	}

	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		m_point_light_availability[i].x = 0;
	}


	return;

	// turns out that manual assignment struct fields is corrupting its alignment lmao


	m_point_light_availability[2].x = 1;
	m_point_light_availability[4].x = 1;

	m_point_lights[2].pos = Vec2(640, 320);
	m_point_lights[4].pos = Vec2(640, 320);
	
	m_point_lights[2].color = Vec3(1, 0, 0);
	m_point_lights[4].color = Vec3(0, 1, 0);
	
	m_point_lights[2].radius = 100;
	m_point_lights[4].radius = 100;
	


	GLint size;
	glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &size);
	log_info("GL_MAX_UNIFORM_BLOCK_SIZE is %d", size);
}

void LightSystem::update()
{
	
}

LightHandle LightSystem::add_point_light()
{
	auto light_handle = get_available_handle(m_point_light_availability, MAX_POINT_LIGHTS);

    return light_handle;
}

LightHandle LightSystem::add_spot_light()
{
   	auto spot_handle = get_available_handle(m_spot_light_availability, MAX_SPOT_LIGHTS);

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

void LightSystem::remove_point_light(LightHandle id)
{
	free_handle(id, m_point_light_availability, MAX_POINT_LIGHTS);
}

void LightSystem::remove_spot_light(LightHandle id)
{
	free_handle(id, m_spot_light_availability, MAX_SPOT_LIGHTS);
}

void LightSystem::prepare_shader(Shader *shd)
{
	glUseProgram(shd->get_id());

	glBindBuffer(GL_UNIFORM_BUFFER, m_uboId);

	glUniformBlockBinding(shd->get_id(), glGetUniformBlockIndex(shd->get_id(), "LightData"), 0);

	const int pld_size = sizeof(PointLightData);
	const int sld_size = sizeof(SpotLightData);

	// data
	glBufferSubData(GL_UNIFORM_BUFFER, 0, pld_size * MAX_POINT_LIGHTS, m_point_lights);
	glBufferSubData(GL_UNIFORM_BUFFER, pld_size * MAX_POINT_LIGHTS, sld_size * MAX_SPOT_LIGHTS, m_spot_lights);

	// availability arrays
	glBufferSubData(GL_UNIFORM_BUFFER, pld_size * MAX_POINT_LIGHTS + sld_size * MAX_SPOT_LIGHTS, sizeof(Vec4) * MAX_POINT_LIGHTS, m_point_light_availability);
	glBufferSubData(GL_UNIFORM_BUFFER, pld_size * MAX_POINT_LIGHTS + sld_size * MAX_SPOT_LIGHTS + sizeof(Vec4) * MAX_POINT_LIGHTS, sizeof(Vec4) * MAX_SPOT_LIGHTS, m_spot_light_availability);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	shd->set_uniform_float("u_ambientStrength", 0);

}

LightHandle LightSystem::get_available_handle(Vec4* availability_array, int max_count)
{
	for (int i = 0; i < max_count; i++)
	{
		if (availability_array[i].x == 0)
		{
			availability_array[i].x = 1;
			return i;
		}
	}
	assert(false/*, "No available light handles"*/);
	return -1;
}

void LightSystem::free_handle(LightHandle hnd, Vec4* availability_array, int max_count)
{
	availability_array[hnd].x = 0;
}

