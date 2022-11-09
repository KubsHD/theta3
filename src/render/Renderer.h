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


class Subtexture
{
public:
	Subtexture(Texture* sheetTex, Vec2 pos, Vec2 size);
	Texture* tex;
	Vec2 texSize;
	unsigned int vboId;
	unsigned int vaoId;
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
	void set_mvp(const glm::mat4& mvp);
	void set_uniform_vec2(String uniformName, Vec2 v);

	void draw_target(Target* tg);
	void draw_tex(Texture* tex, Vec2 pos);
	void draw_subtex(Subtexture* subTex, Vec2 pos);
	void draw_box(Vec2 pos, Vec2 size, Vec3 color);
	void draw_quad();
};