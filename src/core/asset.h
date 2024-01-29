/*****************************************************************//**
 * \file   asset.h
 * \brief  Asset system
 * 
 * \date   January 2023
 *********************************************************************/

#pragma once

#include <core/types.h>


class Renderer;
class Texture;
class Font;
class Sound;
class Atlas;
class Shader;

/// <summary>
/// Class responsible for asset handling
/// </summary>
class Asset
{
private:
	/// <summary>
	/// Cache for textures
	/// </summary>
	static Map<String, Texture*> cache_texture;

	/// <summary>
	/// Cache for sounds
	/// </summary>
	static Map<String, Sound*> cache_sound;
	
	/// <summary>
	/// Cache for fonts
	/// </summary>
	static Map<String, Font*> cache_font;
	
	/// <summary>
	/// Cache for atlases
	/// </summary>
	static Map<String, Atlas*> cache_atlas;

	/// <summary>
	/// Reference to the renderer
	/// </summary>
	Renderer* renderer_ref;



	static bool use_vfs;
public:

	static Vector<char> read_all_bytes(const char* path);


	/// <summary>
	/// Initialize asset system
	/// </summary>
	/// <param name="ren"></param>
	void init(Renderer* ren);

	/// <summary>
	/// Load a texture from a file
	/// </summary>
	/// <param name="path">Path to texture file</param>
	/// <returns></returns>
	static Texture* load_texture(String path);
	static Texture* load_texture(std::vector<char> data);


	/// <summary>
	/// Load a sound from a file
	/// </summary>
	/// <param name="path">Path to file</param>
	/// <returns></returns>
	static Sound* load_sound(String path);

	/// <summary>
	/// Load a font from a file
	/// </summary>
	/// <param name="path">Load font from file</param>
	/// <returns></returns>
	static Font* load_font(String path);

	/// <summary>
	/// Load an atlas from a file
	/// </summary>
	/// <param name="path">Atlas file</param>
	/// <returns></returns>
	static Atlas* load_atlas(String path);

	static Shader* load_shader(String shader_name);

	/// <summary>
	/// Get real path from a virtual one (inside of data folder)
	/// </summary>
	/// <param name="virtualPath"></param>
	/// <returns></returns>
	static const char* get_asset_path(const char* virtualPath);

	/// <summary>
	/// Read a file
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	static std::string read_text_file(String filePath);
};