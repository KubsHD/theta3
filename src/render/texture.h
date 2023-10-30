#pragma once

#include <core/types.h>

/// <summary>
/// Texture class
/// </summary>
class Texture
{
	/// <summary>
	/// Create a texture from file
	/// </summary>
	/// <param name="path">Path to texture</param>
	Texture(String path);

	/// <summary>
	/// Create a texture from raw bytes
	/// </summary>
	/// <param name="data">Raw bytes</param>
	Texture(std::vector<char> data);

	friend struct Atlas;
	friend class Asset;
public:

	~Texture();

	unsigned int id;
	Vec2 size;
};