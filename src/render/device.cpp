#include "device.h"

#include <core/types.h>
#include <lib/glad/glad.h>

#include <render/texture.h>
#include <render/Shader.h>
#include <render/target.h>
#include <render/buffer.h>

#include <core/log.h>

namespace gpu {

	Device* device = nullptr;
	
	void Device::init()
	{
		assert(device == nullptr, "Device already initialized");
		device = new Device();
	}

	Texture* Device::create_texture(const TextureDesc& desc)
	{
		Texture* tex = new Texture();

		tex->size.x = desc.width;
		tex->size.y = desc.height;

		glGenTextures(1, &tex->id);
		glBindTexture(GL_TEXTURE_2D, tex->id);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, desc.width, desc.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, desc.data);
		glGenerateMipmap(GL_TEXTURE_2D);

		assert(tex != nullptr);

		return tex;
	}

	Shader* Device::create_shader(const ShaderDesc& desc)
	{

		// compiling vertex shader
		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &desc.vs, NULL);
		glCompileShader(vertexShader);

		// compile vertex shader - info
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			log_error("ERROR::Vertex Shader Compilation Failed!!!\n %s\n", infoLog);
		}


		// Fragment shader source - color

		// compiling fragment shader 
		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &desc.ps, NULL);
		glCompileShader(fragmentShader);

		// compiling fragment shader - info
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			log_error("ERROR::Fragment Shader Compilation Failed!!!\n %s\n", infoLog);
		}


		// creating program object
		auto id = glCreateProgram();
		Shader* s = new Shader(id);


		glAttachShader(id, vertexShader);
		glAttachShader(id, fragmentShader);
		glLinkProgram(id);

		// creating program object - info
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(id, 512, NULL, infoLog);
			log_error("ERROR::Program Object Linking Failed!!!\n %s\n", infoLog);
		}


		glUseProgram(id);

		// Deleting shaders from memory after we compiled them
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return s;
	}

	Target* Device::create_target(const TargetDesc& desc)
	{
		auto target = new Target();

		if (desc.w == 0 && desc.h == 0)
		{
			target->id = 0;
			return target;
		}

		glGenFramebuffers(1, &target->id);
		glBindFramebuffer(GL_FRAMEBUFFER, target->id);

		glGenTextures(1, &target->texId);
		glBindTexture(GL_TEXTURE_2D, target->texId);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, desc.w, desc.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, desc.type == TargetScalingType::Nearest ? GL_NEAREST : GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, desc.type == TargetScalingType::Nearest ? GL_NEAREST : GL_LINEAR);

		glBindFramebuffer(GL_FRAMEBUFFER, target->id);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, target->texId, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			log_error("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");

		target->target_size = Vec2(desc.w, desc.h);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return target;
	}


	gpu::Buffer* Device::create_buffer(const gpu::BufferDesc& desc)
	{
		return nullptr;
	}

	/*Target::~Target()
	{
		glDeleteTextures(1, &texId);
		glDeleteFramebuffers(1, &id);
	}

	*/

} 
