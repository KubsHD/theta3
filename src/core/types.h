#pragma once

#include <vector>
#include <memory>
#include <string>

#include <glm/glm.hpp>

using Vec2 = glm::vec2;
using Vec3 = glm::vec3;

using String = std::string;

template<typename T>
using Vector = std::vector<T>;

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}
