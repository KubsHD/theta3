#pragma once

#include <core/types.h>

class Texture
{
public:
	Texture(String path);
	int id;
};

class Renderer {
public:
	void init();

	void set_mvp(glm::mat4& mvp);
	void draw_tex(Texture* tex, Vec2 pos);
	void draw_quad();
};