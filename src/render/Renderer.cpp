#include "Renderer.h"

#include <lib/glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <lib/stb_image.h>

glm::mat4 view(1.0f);
glm::mat4 projection;

Texture::Texture(String path)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	id = texture;
}

unsigned int VBO;
unsigned int shaderProgram;
unsigned int VAO;


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

		out vec4 FragColor;

		void main()
		{
			FragColor = texture(u_tex, vTexCoord);
		}
	)";

void Renderer::init()
{
	projection = glm::ortho(0.0f, 320.0f, 180.0f, 0.0f, -1.0f, 1.0f);

	// OpenGL - start
	float vertices[] = {
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
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);



	// using VAOs
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	// telling opengl how to connext vertex data and their atributes
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void Renderer::set_mvp(glm::mat4& mvp)
{
	glUseProgram(shaderProgram);
	int modelLoc = glGetUniformLocation(shaderProgram, "u_mvp");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mvp));
}

void Renderer::draw_tex(Texture* tex, Vec2 pos)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, Vec3(10.0f));
	model = glm::translate(model, Vec3(pos, 0.0f));

	auto mvp = projection * model;
	set_mvp(mvp);

	glBindTexture(GL_TEXTURE_2D, tex->id);
	set_mvp(mvp);
	draw_quad();
}

void Renderer::draw_quad()
{
	glActiveTexture(0);
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
