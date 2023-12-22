#include "subtexture.h"

#include <render/texture.h>
#include <lib/glad/glad.h>
#include "device.h"
#include "buffer.h"

float px_to_ogl(float px, float size)
{
	return px / size;
}

Subtexture::Subtexture(Texture* sheetTex, Vec2 pos, Vec2 size)
{
	tex = sheetTex;
	texSize = size;


	float vertices[] = {
		// pos			// tex
		0.0f, 1.0f,	px_to_ogl(pos.x, sheetTex->size.x),  px_to_ogl(pos.y + size.y, sheetTex->size.y),
		1.0f, 0.0f,	px_to_ogl(pos.x + size.x, sheetTex->size.x),  px_to_ogl(pos.y, sheetTex->size.y),
		0.0f, 0.0f,	px_to_ogl(pos.x, sheetTex->size.x), px_to_ogl(pos.y , sheetTex->size.y),

		0.0f, 1.0f,	px_to_ogl(pos.x, sheetTex->size.x), px_to_ogl(pos.y + size.y, sheetTex->size.y),
		1.0f, 1.0f,	px_to_ogl(pos.x + size.x, sheetTex->size.x), px_to_ogl(pos.y + size.y, sheetTex->size.y),
		1.0f, 0.0f,	px_to_ogl(pos.x + size.x, sheetTex->size.x),px_to_ogl(pos.y, sheetTex->size.y),
	};

	buf = gpu::device->create_buffer(
		{
			{ {2 , GL_FLOAT}, {2, GL_FLOAT } },
			gpu::BindFlags::BIND_VERTEX_BUFFER,
			sizeof(vertices),
			vertices
		}
	);
}

Subtexture::~Subtexture()
{
	//delete tex;
	glDeleteBuffers(1, &this->vaoId);
	glDeleteBuffers(1, &this->vboId);
}