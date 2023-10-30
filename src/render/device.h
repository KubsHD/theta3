#pragma once

class Texture;
class Program;

namespace gpu
{
	Device* create_device();

	class Device {
	public:
		Texture* create_texture();
		Program* create_program();
	};

}