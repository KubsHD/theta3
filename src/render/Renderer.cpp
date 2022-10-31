#include "Renderer.h"

#include <lib/glad/glad.h>
#include <iostream>

unsigned int VBO;
unsigned int shaderProgram;
unsigned int VAO;


void Renderer::init()
{
	// Vertex Shader - vertex positions
	const char* vertexShaderSource = R"(
		#version 400 core
		layout(location = 0) in vec3 aPos;
		void main()
		{
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
		}
	)";

	const char* fragmentShaderSource = R"(
		#version 400 core
		out vec4 FragColor;
		void main()
		{
			FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
		}
	)";


	// OpenGL - start
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.3f, 0.0f
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Renderer::draw_triangle()
{

	// DRAWING TRIANGLE GOD THANK YOU
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
