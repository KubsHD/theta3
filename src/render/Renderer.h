#pragma once

#include <core/types.h>

class Texture
{
public:
	Texture(String path);
	int id;
};

class Target
{
public:
	Target();

	void bind();

	unsigned int id;
	unsigned int texId;
};

class Shader
{
public:
	Shader(const char* vtx, const char* fsx);
	int id;
};

class Renderer {
public:
	void init();

	void set_mvp(glm::mat4& mvp);
	void draw_tex(Texture* tex, Vec2 pos);
	void draw_quad();
};