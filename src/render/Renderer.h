#pragma once

#include <core/types.h>
#include <glm/ext/matrix_transform.hpp>
#include <render/Shader.h>


class Camera {
	glm::mat4 m_viewMatrix;
public:
	Camera() : position(0,0) {
		m_viewMatrix = glm::mat4(1.0f);
	};

	inline glm::mat4 get_matrix() {
		return glm::translate(m_viewMatrix, Vec3(-position, 0.0));
	}

	Vec2 position;
	float zoom = 1.0f;
};

class Window;

class Texture
{
	Texture(String path);

	friend class Asset;
public:
	~Texture();

	unsigned int id;
	Vec2 size;
};


class Subtexture
{
public:
	Subtexture(Texture* sheetTex, Vec2 pos, Vec2 size);
	~Subtexture();
	Texture* tex;
	Vec2 texSize;
	unsigned int vboId;
	unsigned int vaoId;
};

class Target
{
public:
	Target(int w, int h);
	~Target();

	void bind();

	unsigned int id;
	unsigned int texId;

	Vec2 target_size;
};

struct Glyph
{
	int id;
	int x;
	int y;
	int w;
	int h;
	int xoff;
	int yoff;
	int xadv;
	// not used

	int page;
	int chnl;

	Ref<Subtexture> subTex;

	/* data */
};

class Font {
private:
	friend class Asset;
	
	Font(String path);
public:

	String name;
	Texture* atlas;
	Glyph glyphs[200];
};

class Renderer {
	Camera* m_currentCamera;
	Target* m_currentTarget;

	Shader* m_circleShader;
	Shader* m_defaultShader;

public:
	static Target* Backbuffer;
	static Font* DefaultFont;

	void init(Window* win);
	void clear(Vec3 color = Vec3(0.03f, 0.25f, 0.03f));

	void update_size(int w, int h);

	void set_target(Target* tg);
	void set_mvp(const glm::mat4& mvp);
	void set_uniform_vec2(String uniformName, Vec2 v);
	void set_uniform_float(String uniformName, float v);

	// todo: change this to smart pointer or dont forget to cleanup
	inline void set_camera(Camera* cam) { m_currentCamera = cam; };

	void draw_target(Target* tg);
	void draw_tex(Texture* tex, Vec2 pos, float opacity = 1.0f, bool flip = false);
	void draw_subtex(Subtexture* subTex, Vec2 pos, float opacity = 1.0f, float scale = 1.0f, bool flip = false);
	void draw_box(Vec2 pos, Vec2 size, Vec3 color = Vec3(0,0,0));
	void draw_circle(Vec2 pos, float radius, Vec3 color = Vec3(0, 0, 0));
	void draw_quad();
	void draw_text(String text, Font* font, Vec2 pos, float scale = 1.0f, float opacity = 1.0f);
};