#pragma once

#include <core/types.h>

class Window;

class Texture
{
public:
	Texture(String path);
	int id;
	Vec2 size;
};

class Target
{
public:
	Target(int w, int h);

	void bind();

	unsigned int id;
	unsigned int texId;

	Vec2 target_size;
};

class Shader
{
public:
	Shader(const char* vtx, const char* fsx);
	int id;
};

class Renderer {
private:
	Target* m_currentTarget;
public:
	static Target* Backbuffer;

	void init(Window* win);

	void set_target(Target* tg);
	void clear();
	void draw_target(Target* tg);
	void set_mvp(const glm::mat4& mvp);
	void draw_tex(Texture* tex, Vec2 pos);
	void draw_quad();
};