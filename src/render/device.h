#pragma once

class Texture;
class Shader;
class Target;

enum TargetScalingType;

namespace gpu
{

	struct TextureDesc {
		void* data;
		int width;
		int height;
		//int channels;
	};

	struct TargetDesc {
		int w; int h; TargetScalingType type;
	};

	struct ShaderDesc {

	};

	class Device {
	public:
		static void init();
		Texture* create_texture(const TextureDesc& desc);
		Shader* create_program() { return nullptr; };
		Target* create_target(const TargetDesc& desc);
	};

	extern Device* device;
}