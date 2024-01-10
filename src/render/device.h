#pragma once

#include <core/types.h>

class Texture;
class Shader;
class Target;

enum class BindFlags;
enum class TargetScalingType;

struct ShaderDesc;

namespace gpu
{
	struct BufferDesc;
	struct Buffer;
	struct TargetDesc;

	struct TextureDesc {
		void* data;
		int width;
		int height;
		//int channels;
	};

	
	

	class Device {
	public:
		static void init();
		Texture* create_texture(const TextureDesc& desc);
		Shader* create_shader(const ShaderDesc& desc);
		Target* create_target(const TargetDesc& desc);
		Buffer* create_buffer(const BufferDesc& desc);

		void update_buffer(Buffer* buffer, void* data, int size);
	};

	extern Device* device;
}