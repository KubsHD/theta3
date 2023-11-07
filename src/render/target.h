#pragma once

#include <core/types.h>

/// <summary>
/// Describes scaling type of a given texture
/// </summary>
enum class TargetScalingType {
	Nearest,
	Linear
};

namespace gpu {

struct TargetDesc {
		int w; int h; TargetScalingType type;
};

}
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