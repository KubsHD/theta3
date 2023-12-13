#include "Shader.h"


#include <lib/glad/glad.h>
#include <core/asset.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <render/device.h>



void Shader::set_uniform_vec2(String uniformName, Vec2 v)
{
	glUseProgram(get_id());
	int modelLoc = glGetUniformLocation(get_id(), uniformName.c_str());
	glUniform2fv(modelLoc, 1, glm::value_ptr(v));
}

void Shader::set_uniform_mat4(String uniformName, glm::mat4 v)
{
	glUseProgram(get_id());
	int modelLoc = glGetUniformLocation(get_id(), uniformName.c_str());
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(v));
}

void Shader::set_uniform_float(String uniformName, float v)
{
	glUseProgram(get_id());
	int modelLoc = glGetUniformLocation(get_id(), uniformName.c_str());
	glUniform1fv(modelLoc, 1, &v);
}

void Shader::set_uniform_vec3(String uniformName, Vec3 color)
{
	glUseProgram(get_id());
	int modelLoc = glGetUniformLocation(get_id(), uniformName.c_str());
	glUniform3fv(modelLoc, 1, glm::value_ptr(color));
}

void Shader::set_uniform_vec4(String uniformName, glm::vec4 color)
{
	glUseProgram(get_id());
	int modelLoc = glGetUniformLocation(get_id(), uniformName.c_str());
	glUniform4fv(modelLoc, 1, glm::value_ptr(color));
}

void Shader::set_uniform_int(const char* name, int val)
{
	glUseProgram(get_id());
	int modelLoc = glGetUniformLocation(get_id(), name);
	glUniform1iv(modelLoc, 1, &val);
}
