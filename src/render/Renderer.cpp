#include "Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <core/log.h>

#include <filesystem>

#include <core/window.h>

#include <core/game.h>

#include <render/light_system.h>

#include <render/subtexture.h>
#include <render/buffer.h>


#define STB_IMAGE_IMPLEMENTATION
#include <lib/stb_image.h>

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif
#include <core/asset.h>
#include "device.h"
#include <utils/profiler.h>

glm::mat4 view(1.0f);
glm::mat4 projection(1.0f);


unsigned int VBO;
unsigned int VAO;

unsigned int boxVBO;
unsigned int boxVAO;

void Renderer::update()
{
	light->prepare_shader(m_uberShader);
}

void Renderer::init(Window* win)
{
	THETA_PROFILE;

	gpu::Device::init();
	
	Backbuffer = new Target();
	Backbuffer->id = 0;
	Backbuffer->target_size = Vec2(win->w, win->h);

	Viewport = gpu::device->create_target({ 1280, 720, TargetScalingType::Nearest });

	DefaultFont = Asset::load_font("font/monogram.fnt");

	light = new LightSystem();
	light->init();

	// OpenGL - start
	float vertices_old[] = {
		// pos			// tex
		-1.0f, 1.0f,	0.0f, 1.0f,
		1.0f, -1.0f,	1.0f, 0.0f,
		-1.0f, -1.0f,	0.0f, 0.0f,

		-1.0f, 1.0f,	0.0f, 1.0f,
		1.0f, 1.0f,		1.0f, 1.0f,
		1.0f, -1.0f,	1.0f, 0.0f
	};

	float vertices2[] = {
		// pos      // tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);




	// using VAOs
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	// telling opengl how to connext vertex data and their atributes
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// BOX VAO + VBO


	// OpenGL - start
	float vertices_box[] = {
		// pos			// tex
		0.0f, 0.0f,	0.0f, 0.0f,
		0.0f, 1.0f,	0.0f, 1.0f,
		1.0f, 1.0f,		1.0f, 1.0f,
		1.0f, 0.0f,	1.0f, 0.0f,
	};

	glGenBuffers(1, &boxVBO);

	glBindBuffer(GL_ARRAY_BUFFER, boxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_box), vertices_box, GL_STATIC_DRAW);



	glGenVertexArrays(1, &boxVAO);

	glBindVertexArray(boxVAO);
	// telling opengl how to connext vertex data and their atributes
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_circleShader = Asset::load_shader("circle");
	m_defaultShader = Asset::load_shader("default");
	m_filledBoxShader = Asset::load_shader("box");
	m_uberShader = Asset::load_shader("uber");
	m_uiShader = Asset::load_shader("default");
}

Vec2 current_size;

void Renderer::set_target(Target* tg)
{
	m_currentTarget = tg;
	tg->bind();

	projection = glm::ortho(0.0f, tg->target_size.x, tg->target_size.y, 0.0f, -1000.0f, 1000.0f);
	current_size = tg->target_size;

	glViewport(0, 0, tg->target_size.x, tg->target_size.y);
}

void Renderer::clear(Vec3 color)
{
	glClearColor(color.x, color.y, color.z, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}

void Renderer::clear(Vec4 color)
{
	glClearColor(color.x, color.y, color.z, color.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Renderer::update_size(int w, int h)
{
	Backbuffer->target_size = Vec2(w, h);
}

void Renderer::draw_target(Target* tg)
{
	glUseProgram(m_defaultShader->get_id());

	// fix opacity not being 1.0 by default
	m_defaultShader->set_uniform_float("u_opacity", 1.0f);

	glBindTexture(GL_TEXTURE_2D, tg->texId);
	
	auto size = tg->target_size;

	glm::mat4 model = glm::mat4(1.0f);

	float scale = min((float)current_size.x / size.x, (float)current_size.y / size.y);

	//SDL_RenderCopy(ren, current_camera->target, NULL,
	//	&(SDL_Rect)
	// {w / 2 - (current_camera->size.x / 2 * scale),  x
	//	h / 2 - (current_camera->size.y / 2 * scale),  y
	//	current_camera->size.x* scale,				   w
	//	current_camera->size.y* scale});			   h


	model = glm::translate(model, Vec3(current_size.x / 2 - (size.x / 2 * scale), current_size.y / 2 - (size.y / 2 * scale), 0.0f));
	model = glm::scale(model, Vec3(size.x * scale, size.y * scale, 1.0f));

	m_defaultShader->set_uniform_mat4("u_mvp", projection * model);
	
	glUseProgram(m_defaultShader->get_id());
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}



void Renderer::draw_tex(Texture* tex, Vec2 pos, float opacity, bool flip)
{
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, Vec3(pos, 0.0f));
	//model = glm::translate(model, glm::vec3(tex->size.x,tex->size.y, 0.0f)); 

	if (flip)
	{
		model = glm::translate(model, glm::vec3(tex->size.x, 0.0f, 0.0f)); 
		model = glm::scale(model, Vec3(-1.0f, 1.0f, 1.0f));
	}

	model = glm::scale(model, Vec3(tex->size.x, tex->size.y, 1.0f));

	auto mvp = projection * (m_currentCamera != nullptr ? m_currentCamera->get_matrix() : glm::mat4(1.0f)) * model;

	glBindTexture(GL_TEXTURE_2D, tex->id);

	set_required_uniforms(m_uberShader, mvp, opacity, model);
	light->prepare_shader(m_uberShader);

	draw_quad();
	glBindTexture(GL_TEXTURE_2D, 0);

	m_uberShader->set_uniform_float("u_opacity", 1.0f);
}

void Renderer::set_required_uniforms(Shader* s, glm::mat4 mvp, float opacity, glm::mat4 model)
{
	s->set_uniform_float("u_opacity", opacity);
	s->set_uniform_mat4("u_mvp", mvp);
	s->set_uniform_mat4("u_model", model);
	s->set_uniform_float("u_time", Game::get_time());
}


void Renderer::draw_tex_s(Texture* tex, Vec2 pos, Vec2 size, Shader* custom_shader /*= nullptr*/, float opacity /*= 1.0f*/, bool flip /*= false*/)
{
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, Vec3(pos, 0.0f));
	//model = glm::translate(model, glm::vec3(tex->size.x,tex->size.y, 0.0f)); 

	if (flip)
	{
		model = glm::translate(model, glm::vec3(tex->size.x, 0.0f, 0.0f));
		model = glm::scale(model, Vec3(size, 1.0f) * Vec3(-1.0f, 1.0f, 1.0f));
	}

	model = glm::scale(model, Vec3(size.x, size.y, 1.0f));

	auto mvp = projection * (m_currentCamera != nullptr ? m_currentCamera->get_matrix() : glm::mat4(1.0f)) * model;

	glUseProgram(custom_shader->get_id());

	glBindTexture(GL_TEXTURE_2D, tex->id);

	set_required_uniforms(custom_shader, mvp, opacity, model);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindTexture(GL_TEXTURE_2D, 0);

	custom_shader->set_uniform_float("u_opacity", 1.0f);

	glUseProgram(0);
}

static GLuint currently_bound_tex_id= 99999;

void Renderer::draw_subtex(Subtexture* subTex, Vec2 pos, float opacity, float scale, bool flip)
{
	glm::mat4 model = glm::mat4(1.0f);


	model = glm::translate(model, Vec3(pos, 0.0f));
	//model = glm::translate(model, glm::vec3(subTex->texSize.x, subTex->texSize.y, 0.0f));
	if (flip)
	{
		model = glm::translate(model, glm::vec3(subTex->texSize.x,0.0f, 0.0f));
		model = glm::scale(model, Vec3(-1.0f, 1.0f, 1.0f));
	}

	model = glm::scale(model, Vec3(subTex->texSize.x * scale, subTex->texSize.y * scale, 1.0f));

	auto mvp = projection * (m_currentCamera != nullptr ? m_currentCamera->get_matrix() : glm::mat4(1.0f)) * model;

	set_required_uniforms(m_uberShader, mvp, opacity, model);
	light->prepare_shader(m_uberShader);
	
	glUseProgram(m_uberShader->get_id());


	glBindTexture(GL_TEXTURE_2D, subTex->tex->id);

	glBindVertexArray(subTex->buf->vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindTexture(GL_TEXTURE_2D, 0);

	m_uberShader->set_uniform_float("u_opacity", 1.0f);

}

void Renderer::draw_subtex_s(Subtexture* subTex, Vec2 pos, Shader* shd, float opacity /*= 1.0f*/, float scale /*= 1.0f*/, bool flip /*= false*/)
{
	THETA_PROFILE;

	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, Vec3(pos, 0.0f));
	//model = glm::translate(model, glm::vec3(subTex->texSize.x, subTex->texSize.y, 0.0f));
	if (flip)
	{
		model = glm::translate(model, glm::vec3(subTex->texSize.x, 0.0f, 0.0f));
		model = glm::scale(model, Vec3(-1.0f, 1.0f, 1.0f));
	}

	model = glm::scale(model, Vec3(subTex->texSize.x * scale, subTex->texSize.y * scale, 1.0f));

	auto mvp = projection * (m_currentCamera != nullptr ? m_currentCamera->get_matrix() : glm::mat4(1.0f)) * model;

	set_required_uniforms(shd, mvp, opacity, model);

	glUseProgram(shd->get_id());
	glBindTexture(GL_TEXTURE_2D, subTex->tex->id);

	glBindVertexArray(subTex->buf->vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindTexture(GL_TEXTURE_2D, 0);

	shd->set_uniform_float("u_opacity", 1.0f);
}

void Renderer::draw_box(Vec2 pos, Vec2 size, Vec3 color, bool fill)
{
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, Vec3(pos, 0.0f));
	//model = glm::translate(model, glm::vec3(size.x, size.y, 0.0f));

	model = glm::scale(model, Vec3(size.x, size.y, 1.0f));

	auto mvp = projection * (m_currentCamera != nullptr ? m_currentCamera->get_matrix() : glm::mat4(1.0f)) * model;


	m_filledBoxShader->set_uniform_mat4("u_mvp", mvp);
	m_filledBoxShader->set_uniform_vec3("u_color", color);
	m_filledBoxShader->set_uniform_float("u_opacity", 1.0f);

	m_defaultShader->set_uniform_mat4("u_mvp", mvp);
	m_defaultShader->set_uniform_vec3("u_color", color);
	m_defaultShader->set_uniform_float("u_opacity", 1.0f);


	
	if (fill)
	{
		glUseProgram(m_filledBoxShader->get_id());
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	else
	{
		glUseProgram(m_defaultShader->get_id());
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(boxVAO);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

// Draw a circle WARNING: position is circle's origin point!!!!!!!
void Renderer::draw_circle(Vec2 pos, float radius, Vec3 color)
{
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, Vec3(pos, 0.0f));
	model = glm::translate(model, glm::vec3(-(radius / 2), -(radius / 2), 0.0f));
	model = glm::scale(model, Vec3(radius, radius, 1.0f));


	auto mvp = projection * (m_currentCamera != nullptr ? m_currentCamera->get_matrix() : glm::mat4(1.0f)) * model;



	m_circleShader->set_uniform_mat4("u_mvp", mvp);
	m_circleShader->set_uniform_vec3("u_circleColor", color);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::draw_quad()
{
	glUseProgram(m_uberShader->get_id());
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::draw_text(String text, Font* font, Vec2 pos, float scale, float opacity)
{
	THETA_PROFILE;

	int adv = 0;

	for (int i = 0; text[i]; i++) {
		if (text[i] >= 32 && text[i] < 128) {

			Glyph g = font->glyphs[text[i]];

			SDL_Rect src = { g.x,  g.y,  g.w,  g.h };

			//SDL_FRect dest = { pos.x + (g.xoff + adv), pos.y + g.yoff , g.w , g.h };


			//SDL_RenderCopyF(ren, font->atlas->ptr, &src, &dest);
			
			draw_subtex_s(g.subTex.get(), Vec2(pos.x + (g.xoff + adv), pos.y + g.yoff), m_uiShader, opacity, scale);
			//draw_box(Vec2(pos.x + (g.xoff + adv), pos.y + g.yoff), Vec2(g.w, g.h), Vec3(1, 1, 1));
			adv += g.xadv;

		}
	}
}


void Renderer::draw_box_s(Vec2 pos, Vec2 size, Vec3 color, Shader* shd)
{
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, Vec3(pos, 0.0f));
	//model = glm::translate(model, glm::vec3(size.x, size.y, 0.0f));

	model = glm::scale(model, Vec3(size.x, size.y, 1.0f));

	auto mvp = projection * (m_currentCamera != nullptr ? m_currentCamera->get_matrix() : glm::mat4(1.0f)) * model;



	glUseProgram(shd->get_id());

	shd->set_uniform_mat4("u_mvp", mvp);
	shd->set_uniform_float("u_time", Game::get_time());

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindTexture(GL_TEXTURE_2D, 0);
}


void Renderer::ui_draw_box(Vec2 pos, Vec2 size, Vec3 color /*= Vec3(0, 0, 0)*/, bool fill /*= false*/)
{
	auto cam = m_currentCamera;
	set_camera(nullptr);
	draw_box(pos, size, color, fill);
	set_camera(cam);
}

Camera* Renderer::get_camera()
{
	return m_currentCamera;
}

void Renderer::draw_vao(GLuint vao, Shader* shd, glm::mat4 model)
{
	
	auto mvp = projection * (m_currentCamera != nullptr ? m_currentCamera->get_matrix() : glm::mat4(1.0f)) * model;

	glUseProgram(shd->get_id());
	shd->set_uniform_mat4("u_mvp", mvp);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}



void Renderer::draw_buffer(gpu::Buffer* buffer, int vertex_count, glm::mat4 model, Texture* tex)
{
	if (vertex_count == 0) {
		return;
	}

	auto mvp = projection * (m_currentCamera != nullptr ? m_currentCamera->get_matrix() : glm::mat4(1.0f)) * model;

	glUseProgram(m_uberShader->get_id());

	set_required_uniforms(m_uberShader, mvp, 1.0f, model);
	light->prepare_shader(m_uberShader);

	glBindTexture(GL_TEXTURE_2D, tex->id);
	glBindVertexArray(buffer->vao);
	glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}

Target* Renderer::Backbuffer;
Target* Renderer::Viewport;
Font* Renderer::DefaultFont;



void Renderer::ui_draw_tex(Texture* tex, Vec2 pos, float opacity /*= 1.0f*/, bool flip /*= false*/)
{
	auto cam = m_currentCamera;
	set_camera(nullptr);
	draw_tex_s(tex, pos, tex->size, m_uiShader, opacity, flip);
	set_camera(cam);
}

void Renderer::ui_draw_text(String text, Font* font, Vec2 pos, float scale /*= 1.0f*/, float opacity /*= 1.0f*/)
{
	auto cam = m_currentCamera;
	set_camera(nullptr);

	int adv = 0;

	for (int i = 0; text[i]; i++) {
		if (text[i] >= 32 && text[i] < 128) {

			Glyph g = font->glyphs[text[i]];

			SDL_Rect src = { g.x,  g.y,  g.w,  g.h };

			//SDL_FRect dest = { pos.x + (g.xoff + adv), pos.y + g.yoff , g.w , g.h };


			//SDL_RenderCopyF(ren, font->atlas->ptr, &src, &dest);

			draw_subtex_s(g.subTex.get(), Vec2(pos.x + (g.xoff + adv), pos.y + g.yoff), m_uiShader, opacity, scale);
			//draw_box(Vec2(pos.x + (g.xoff + adv), pos.y + g.yoff), Vec2(g.w, g.h), Vec3(1, 1, 1));
			adv += g.xadv;

		}
	}

	set_camera(cam);
}

