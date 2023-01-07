#pragma once

#include <core/types.h>

class Shader {
public:
	Shader(String shaderName);

	int get_id() {
		return id;
	};

	void set_uniform_vec2(String uniformName, Vec2 v);
	void set_uniform_mat4(String uniformName, glm::mat4 v);
	void set_uniform_float(String uniformName, float v);

private:
	int id;
public:
	void set_uniform_vec3(String uniformName, Vec3 color);
	void set_uniform_vec4(String uniformName, glm::vec4 color);
};
