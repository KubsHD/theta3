#pragma once

#include <core/types.h>

/// <summary>
/// Describes scaling type of a given texture
/// </summary>
enum TargetScalingType {
	Nearest,
	Linear
};

/// <summary>
/// A texture that things can be rendered into
/// </summary>
class Target
{
public:
	void bind();

	unsigned int id;
	unsigned int texId;

	Vec2 target_size;
};