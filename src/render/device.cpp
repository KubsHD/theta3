#include "device.h"

#include <core/types.h>

#include <render/texture.h>
#include <lib/glad/glad.h>

#include <render/target.h>
#include <core/log.h>

namespace gpu {

	Device* device;
	
	void Device::init()
	{
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


	/*Target::~Target()
	{
		glDeleteTextures(1, &texId);
		glDeleteFramebuffers(1, &id);
	}

	*/

}
