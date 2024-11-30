/*****************************************************************//**
 * \file   types.h
 * \brief  Type aliases
 * 
 * \date   January 2023
 *********************************************************************/

#pragma once

#include <vector>
#include <memory>
#include <filesystem>
#include <string>
#include <map>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <functional>
#include <list>
#include <cassert>

#include <SDL.h>
#include <glm/glm.hpp>
#include <lib/imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>


using Vec2 = glm::vec2;
using Vec3 = glm::vec3;
using Vec4 = glm::vec4;

using String = std::string;

using Path = std::filesystem::path;

template<typename T>
using Vector = std::vector<T>;

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename K, typename V>
using Map = std::map<K,V>;

template<typename K, typename V>
using UnorderedMap = std::unordered_map<K, V>;