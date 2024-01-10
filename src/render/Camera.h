#pragma once

#include <core/types.h>
#include <glm/glm.hpp>

/// <summary>
/// Scene Camera
/// </summary>
class Camera {
	glm::mat4 m_projMatrix;
	glm::mat4 m_viewMatrix;
public:

	/// <summary>
	/// Create a camera
	/// </summary>
	Camera() : position(0, 0) {
		m_viewMatrix = glm::mat4(1.0f);
	};

	/// <summary>
	/// Get camera's view matrix
	/// </summary>
	/// <returns></returns>
	inline glm::mat4 get_matrix() {
		return glm::scale(glm::translate(m_viewMatrix, Vec3(-position, 0.0)), Vec3(zoom, zoom, 1.0));
	}

	Vec2 position;
	float zoom = 1.0f;
};
