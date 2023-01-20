/*****************************************************************//**
 * \file   atl.h
 * \brief  Atlas file format
 * 
 * \date   January 2023
 *********************************************************************/

#pragma once

#include <cereal/types/unordered_map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>

#include <lib/json.hpp>
#include <cereal/archives/json.hpp>
#include <core/asset.h>
#include <fstream>
#include <render/Renderer.h>

namespace glm
{

	template<class Archive> void serialize(Archive& archive, glm::vec2& v) { archive(v.x, v.y); }
	template<class Archive> void serialize(Archive& archive, glm::vec3& v) { archive(v.x, v.y, v.z); }
	template<class Archive> void serialize(Archive& archive, glm::vec4& v) { archive(v.x, v.y, v.z, v.w); }
	template<class Archive> void serialize(Archive& archive, glm::ivec2& v) { archive(v.x, v.y); }
	template<class Archive> void serialize(Archive& archive, glm::ivec3& v) { archive(v.x, v.y, v.z); }
	template<class Archive> void serialize(Archive& archive, glm::ivec4& v) { archive(v.x, v.y, v.z, v.w); }
	template<class Archive> void serialize(Archive& archive, glm::uvec2& v) { archive(v.x, v.y); }
	template<class Archive> void serialize(Archive& archive, glm::uvec3& v) { archive(v.x, v.y, v.z); }
	template<class Archive> void serialize(Archive& archive, glm::uvec4& v) { archive(v.x, v.y, v.z, v.w); }
	template<class Archive> void serialize(Archive& archive, glm::dvec2& v) { archive(v.x, v.y); }
	template<class Archive> void serialize(Archive& archive, glm::dvec3& v) { archive(v.x, v.y, v.z); }
	template<class Archive> void serialize(Archive& archive, glm::dvec4& v) { archive(v.x, v.y, v.z, v.w); }

	// glm matrices serialization
	template<class Archive> void serialize(Archive& archive, glm::mat2& m) { archive(m[0], m[1]); }
	template<class Archive> void serialize(Archive& archive, glm::dmat2& m) { archive(m[0], m[1]); }
	template<class Archive> void serialize(Archive& archive, glm::mat3& m) { archive(m[0], m[1], m[2]); }
	template<class Archive> void serialize(Archive& archive, glm::mat4& m) { archive(m[0], m[1], m[2], m[3]); }
	template<class Archive> void serialize(Archive& archive, glm::dmat4& m) { archive(m[0], m[1], m[2], m[3]); }

	template<class Archive> void serialize(Archive& archive, glm::quat& q) { archive(q.x, q.y, q.z, q.w); }
	template<class Archive> void serialize(Archive& archive, glm::dquat& q) { archive(q.x, q.y, q.z, q.w); }

}

inline std::string removeSpaces(std::string s) {
	std::string tmp(s);
	tmp.erase(std::remove(tmp.begin(), tmp.end(), ' '), tmp.end());
	return tmp;
}

inline std::vector<char> ReadAllBytes(std::string filename)
{
	std::ifstream ifs(removeSpaces(filename), std::ios::binary | std::ios::ate);
	std::ifstream::pos_type pos = ifs.tellg();

	std::vector<char>  result(pos);

	ifs.seekg(0, std::ios::beg);
	ifs.read(&result[0], pos);

	ifs.close();

	return result;
}

/// <summary>
/// Atlas sprite data
/// </summary>
struct AtlasSprite {
	AtlasSprite() : pos(0, 0), size(0, 0), sprite_name("NONE") {};
	AtlasSprite(Vec2 p, Vec2 s) : pos(p), size(s), sprite_name("name") {};
	
	/// <summary>
	/// Sprite name
	/// </summary>
	String sprite_name;

	/// <summary>
	/// Sprite position in root texture
	/// </summary>
	Vec2 pos;

	/// <summary>
	/// Sprite size in root texture
	/// </summary>
	Vec2 size;

	template <class Archive>
	void serialize(Archive& ar)
	{
		ar(sprite_name, pos, size);
	}
};

/// <summary>
/// Atlas data
/// </summary>
struct AtlasData {
	/// <summary>
	/// Name of the atlas
	/// </summary>
	String name;

	/// <summary>
	/// Texture data
	/// </summary>
	Vector<char> tex_data;
	
	/// <summary>
	/// Texture data size
	/// </summary>
	uint32_t tex_data_size;

	/// <summary>
	/// Sprites array
	/// </summary>
	Vector<AtlasSprite> sprites;

	/// <summary>
	/// Sprites count
	/// </summary>
	uint32_t sprites_count;

	template <class Archive>
	void serialize(Archive& ar)
	{
		ar(name, tex_data, tex_data_size, sprites, sprites_count);
	}

	/// <summary>
	/// Convert from .json + .png to .atl
	/// </summary>
	/// <param name="path"></param>
	static void convert_from_json(String path)
	{
		AtlasData dat;

		//load raw file
		dat.name = Path(std::string(path + ".json")).filename().stem().string();

		std::ifstream ifs(std::string(path + ".json"));
		auto data = nlohmann::json::parse(ifs);

		ifs.close();

		for (auto frame : data["frames"])
		{
			dat.sprites.push_back(AtlasSprite(
				{ frame["frame"]["x"], frame["frame"]["y"] },
				{ frame["frame"]["w"], frame["frame"]["h"] }
			));
		}

		dat.sprites_count = dat.sprites.size();


		dat.tex_data = ReadAllBytes(std::string(path + ".png"));

		std::ofstream os(path + ".atl", std::ios::binary);
		cereal::BinaryOutputArchive archive(os);

		archive(dat);



		//std::filesystem::remove(Path(std::string(path + ".json")));
		//std::filesystem::remove(Path(std::string(path + ".png")));
	}
};

/// <summary>
/// Runtime atlas class
/// </summary>
struct Atlas {

	/// <summary>
	/// Load atlas from .atl file
	/// </summary>
	/// <param name="path">Path to file</param>
	Atlas(String path)
	{
		name = Path(std::string(path)).filename().stem().string();

		//log_info("Loaded anim: %s\n", ad.name);

		std::ifstream os(std::string(path) + std::string(".atl"), std::ios::binary);
		cereal::BinaryInputArchive archive(os);

		archive(dat);

		atlas_tex = new Texture(dat.tex_data);

		for (auto frame : dat.sprites)
		{
			Frames.push_back(new Subtexture
				{ 
					atlas_tex,
					frame.pos,
					frame.size
				}
			);
		}
	}

	/// <summary>
	/// Atlas data
	/// </summary>
	AtlasData dat;

	/// <summary>
	/// Atlas texture
	/// </summary>
	Texture* atlas_tex;

	/// <summary>
	/// Atlas name
	/// </summary>
	String name;

	/// <summary>
	/// Frames array
	/// </summary>
	Vector<Subtexture*> Frames;
};