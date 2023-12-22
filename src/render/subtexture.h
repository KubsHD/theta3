#pragma once

#include <core/types.h>
#include <glm/ext/matrix_transform.hpp>

class Texture;
class Window;
class Target;
class LightSystem;

namespace gpu {
	struct Buffer;
};

/// <summary>
/// Texture inside of another texture
/// </summary>
class Subtexture
{
public:

	/// <summary>
	/// Create a subtexture
	/// </summary>
	/// <param name="sheetTex">Root texture</param>
	/// <param name="pos">Position of subtexture's top-left corner in a root texture (in px)</param>
	/// <param name="size">Size of a subtexture</param>
	Subtexture(Texture* sheetTex, Vec2 pos, Vec2 size);
	~Subtexture();
	Texture* tex;
	Vec2 texSize;

	gpu::Buffer* buf;

	unsigned int vboId;
	unsigned int vaoId;
};