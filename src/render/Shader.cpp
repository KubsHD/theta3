#include "Shader.h"


#include <lib/glad/glad.h>
#include <core/asset.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(String shaderName)
{
	String vertexShaderSource = Asset::read_file("shader/" + shaderName + ".vs");
	String fragmentShaderSource = Asset::read_file("shader/" + shaderName + ".fs");
	const char* data;



	data = vertexShaderSource.c_str();

	// compiling vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &data, NULL);
	glCompileShader(vertexShader);

	// compile vertex shader - info
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::Vertex Shader Compilation Failed!!!\n" << infoLog << std::endl;
	}


	// Fragment shader source - color

	data = fragmentShaderSource.c_str();
	// compiling fragment shader 
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &data, NULL);
	glCompileShader(fragmentShader);

	// compiling fragment shader - info
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::Fragment Shader Compilation Failed!!!\n" << infoLog << std::endl;
	}


	// creating program object
	id = glCreateProgram();

	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);

	// creating program object - info
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::Program Object Linking Failed!!!\n" << infoLog << std::endl;
	}


	glUseProgram(id);

	// Deleting shaders from memory after we compiled them
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

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
