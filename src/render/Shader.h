/*****************************************************************//**
 * \file   Shader.h
 * \brief  Shader class
 * 
 * \date   January 2023
 *********************************************************************/
#pragma once

#include <core/types.h>

/// <summary>
/// Responsible for managing a shader object and communication with it
/// </summary>
class Shader {
public:

	/// <summary>
	/// Create a shader program (vertex + fragment shaders) from a pair of files with .vs and .fs extension
	/// </summary>
	/// <param name="shaderName">Shader name</param>
	Shader(String shaderName);

	/// <summary>
	/// Return shader program object id
	/// </summary>
	/// <returns></returns>
	int get_id() {
		return id;
	};
	
	/// <summary>
	/// Set shader's vec2 uniform
	/// </summary>
	/// <param name="uniformName">Uniform name</param>
	/// <param name="v">Vec2 value</param>
	void set_uniform_vec2(String uniformName, Vec2 v);

	/// <summary>
	/// Set shader's mat4 uniform
	/// </summary>
	/// <param name="uniformName">Uniform name</param>
	/// <param name="v">mat4 value</param>
	void set_uniform_mat4(String uniformName, glm::mat4 v);

	/// <summary>
	/// Set shader's float uniform
	/// </summary>
	/// <param name="uniformName">Uniform name</param>
	/// <param name="v">float value</param>
	void set_uniform_float(String uniformName, float v);

private:
	int id;
public:
	
	/// <summary>
	/// Set shader's vec3 uniform
	/// </summary>
	/// <param name="uniformName">Uniform name</param>
	/// <param name="color">Vec3 value</param>
	void set_uniform_vec3(String uniformName, Vec3 color);

	/// <summary>
	/// Set shader's vec4 uniform
	/// </summary>
	/// <param name="uniformName">Uniform name</param>
	/// <param name="color">Vec4 value</param>
	void set_uniform_vec4(String uniformName, glm::vec4 color);
};
