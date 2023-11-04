#pragma once

#include <core/types.h>

/// <summary>
/// Texture class
/// </summary>
struct Texture
{
	friend struct Atlas;
	friend class Asset;
public:

	unsigned int id;
	Vec2 size;
};