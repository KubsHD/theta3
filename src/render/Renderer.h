#pragma once

#include <core/types.h>

class Texture
{
	Texture(String path);

	int id;
};

class Renderer {
public:
	void init();

	void draw_tex(Texture& tex, Vec2 pos);
	void draw_triangle();
};