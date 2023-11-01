#pragma once

#include <core/types.h>

class Texture;
class Shader;
class Target;

enum BindFlags;
enum TargetScalingType;

struct ShaderDesc;

namespace gpu
{
	struct BufferDesc;
	struct Buffer;

	struct TextureDesc {
		void* data;
		int width;
		int height;
		//int channels;
	};

	struct TargetDesc {
		int w; int h; TargetScalingType type;
	};
	

	class Device {
	public:
		static void init();
		Texture* create_texture(const TextureDesc& desc);
		Shader* create_shader(const ShaderDesc& desc);
		Target* create_target(const TargetDesc& desc);
		Buffer* create_buffer(const BufferDesc& desc);
	};

	extern Device* device;
}