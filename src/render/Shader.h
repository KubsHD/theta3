#pragma once

#include <core/types.h>

class Shader {
public:
	Shader(String shaderName);

	int get_id() {
		return id;
	};
private:
	int id;
};
