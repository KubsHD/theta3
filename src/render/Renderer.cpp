#include "Renderer.h"

#include <lib/glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include <filesystem>

#include <core/window.h>

#define STB_IMAGE_IMPLEMENTATION
#include <lib/stb_image.h>

glm::mat4 view(1.0f);
glm::mat4 projection;

Texture::Texture(String path)
{
	assert(std::filesystem::exists(path), "Texture does not exist on disk!");

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load and generate the texture
	int width, height, nrChannels;


	//stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		size.x = width;
		size.y = height;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

unsigned int shaderProgram;

unsigned int VBO;
unsigned int VAO;

unsigned int boxVBO;
unsigned int boxVAO;

const char* vertexShaderSource = R"(
		#version 330 core
		layout(location = 0) in vec2 aPos;
		layout(location = 1) in vec2 aTexCoord;
		
		uniform mat4 u_mvp;

		out vec2 vTexCoord;

		void main()
		{
			vTexCoord = aTexCoord;
			gl_Position = u_mvp * vec4(aPos.x, aPos.y, 0.0, 1.0);
		}
	)";


const char* fragmentShaderSource = R"(
		#version 330 core
		in vec2 vTexCoord;
		
		uniform sampler2D u_tex;

		uniform vec2 u_spritePos;
		uniform vec2 u_spriteSize;


		out vec4 FragColor;

		void main()
		{
			FragColor = texture(u_tex, vTexCoord);
		}
	)";

void Renderer::init(Window* win)
{
	Backbuffer = new Target(0,0);
	Backbuffer->id = 0;
	Backbuffer->target_size = Vec2(win->w, win->h);

	// OpenGL - start
	float vertices[] = {
		// pos			// tex
		-1.0f, 1.0f,	0.0f, 1.0f,
		1.0f, -1.0f,	1.0f, 0.0f,
		-1.0f, -1.0f,	0.0f, 0.0f,

		-1.0f, 1.0f,	0.0f, 1.0f,
		1.0f, 1.0f,		1.0f, 1.0f,
		1.0f, -1.0f,	1.0f, 0.0f
	};

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// compiling vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// compile vertex shader - info
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::Vertex Shader Compilation Failed!!!\n" << infoLog << std::endl;
	}


	// Fragment shader source - color

	// compiling fragment shader 
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// compiling fragment shader - info
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::Fragment Shader Compilation Failed!!!\n" << infoLog << std::endl;
	}


	// creating program object
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// creating program object - info
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::Program Object Linking Failed!!!\n" << infoLog << std::endl;
	}


	glUseProgram(shaderProgram);

	// Deleting shaders from memory after we compiled them
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



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
		-1.0f, -1.0f,	0.0f, 0.0f,
		-1.0f, 1.0f,	0.0f, 1.0f,
		1.0f, 1.0f,		1.0f, 1.0f,
		1.0f, -1.0f,	1.0f, 0.0f,
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
}

void Renderer::set_target(Target* tg)
{
	tg->bind();
	projection = glm::ortho(0.0f, tg->target_size.x, tg->target_size.y, 0.0f, -1.0f, 1.0f);
	glViewport(0, 0, tg->target_size.x, tg->target_size.y);
}

void Renderer::clear()
{
	glClearColor(0.03f, 0.25f, 0.03f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw_target(Target* tg)
{
	glBindTexture(GL_TEXTURE_2D, tg->texId);
	set_mvp(glm::mat4(1.0f));
	draw_quad();
}

void Renderer::set_mvp(const glm::mat4& mvp)
{
	glUseProgram(shaderProgram);
	int modelLoc = glGetUniformLocation(shaderProgram, "u_mvp");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mvp));
}

void Renderer::set_uniform_vec2(String uniformName, Vec2 v)
{
	glUseProgram(shaderProgram);
	int modelLoc = glGetUniformLocation(shaderProgram, uniformName.c_str());
	glUniform2fv(modelLoc, 1, glm::value_ptr(v));
}

void Renderer::draw_tex(Texture* tex, Vec2 pos)
{
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, Vec3(pos, 0.0f));
	model = glm::translate(model, glm::vec3(tex->size.x,tex->size.y, 0.0f)); 
	model = glm::scale(model, Vec3(tex->size.x, tex->size.y, 1.0f));

	auto mvp = projection * (m_currentCamera != nullptr ? m_currentCamera->get_matrix() : glm::mat4(1.0f)) * model;

	glBindTexture(GL_TEXTURE_2D, tex->id);
	set_mvp(mvp);
	draw_quad();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::draw_subtex(Subtexture* subTex, Vec2 pos)
{
	glm::mat4 model = glm::mat4(1.0f);


	model = glm::translate(model, Vec3(pos, 0.0f));
	model = glm::translate(model, glm::vec3(subTex->texSize.x, subTex->texSize.y, 0.0f));
	model = glm::scale(model, Vec3(1.0f, -1.0f, 1.0f));
	model = glm::scale(model, Vec3(subTex->texSize.x, subTex->texSize.y, 1.0f));

	auto mvp = projection * (m_currentCamera != nullptr ? m_currentCamera->get_matrix() : glm::mat4(1.0f)) * model;


	set_mvp(mvp);
	
	glUseProgram(shaderProgram);
	glBindTexture(GL_TEXTURE_2D, subTex->tex->id);
	
	glBindVertexArray(subTex->vaoId);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::draw_box(Vec2 pos, Vec2 size, Vec3 color)
{
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, Vec3(pos, 0.0f));
	model = glm::translate(model, glm::vec3(size.x, size.y, 0.0f));
	model = glm::scale(model, Vec3(size.x, size.y, 1.0f));

	auto mvp = projection * (m_currentCamera != nullptr ? m_currentCamera->get_matrix() : glm::mat4(1.0f)) * model;


	set_mvp(mvp);
	
	glUseProgram(shaderProgram);
	glBindVertexArray(boxVAO);
	glDrawArrays(GL_LINE_LOOP, 0, 4);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::draw_quad()
{
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

Target* Renderer::Backbuffer;

Target::Target(int w, int h)
{
	if (w == 0 && h == 0)
	{
		id = 0;
		return;
	}

	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);

	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindFramebuffer(GL_FRAMEBUFFER, id);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texId, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

	target_size = Vec2(w,h);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Target::~Target()
{
	glDeleteTextures(1, &texId);
	glDeleteFramebuffers(1, &id);
}

void Target::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	glViewport(0, 0, target_size.x, target_size.y);
}

Shader::Shader(const char* vtx, const char* fsx)
{
}

float px_to_ogl(float px, float size)
{
	return px / size;
}

Subtexture::Subtexture(Texture* sheetTex, Vec2 pos, Vec2 size)
{
	tex = sheetTex;
	texSize = size;

	float vertices1[] = {
		// pos			// tex
		-1.0f, 1.0f,	0.0f, 1.0f,
		1.0f, -1.0f,	1.0f, 0.0f,
		-1.0f, -1.0f,	0.0f, 0.0f,

		-1.0f, 1.0f,	0.0f, 1.0f,
		1.0f, 1.0f,		1.0f, 1.0f,
		1.0f, -1.0f,	1.0f, 0.0f
	};


	float vertices[] = {
		// pos			// tex
		-1.0f, 1.0f,	px_to_ogl(pos.x, sheetTex->size.x),  px_to_ogl(pos.y, sheetTex->size.y),
		1.0f, -1.0f,	px_to_ogl(pos.x + size.x, sheetTex->size.x),  px_to_ogl(pos.y + size.y, sheetTex->size.y),
		-1.0f, -1.0f,	px_to_ogl(pos.x, sheetTex->size.x), px_to_ogl(pos.y + size.y, sheetTex->size.y),

		-1.0f, 1.0f,	px_to_ogl(pos.x, sheetTex->size.x), px_to_ogl(pos.y, sheetTex->size.y),
		1.0f, 1.0f,		px_to_ogl(pos.x + size.x, sheetTex->size.x), px_to_ogl(pos.y, sheetTex->size.y),
		1.0f, -1.0f,	px_to_ogl(pos.x + size.x, sheetTex->size.x),px_to_ogl(pos.y + size.y, sheetTex->size.y),
	};

	glGenBuffers(1, &vboId);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// using VAOs
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);
	// telling opengl how to connext vertex data and their atributes
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Subtexture::~Subtexture()
{
	delete tex;
	glDeleteBuffers(1, &this->vaoId);
	glDeleteBuffers(1, &this->vboId);
}

