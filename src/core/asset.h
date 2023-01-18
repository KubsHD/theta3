#pragma once

#include <core/types.h>

class Renderer;
class Texture;
class Font;
class Sound;
class Atlas;

class Asset
{
private:
	static Map<String, Texture*> cache_texture;
	static Map<String, Sound*> cache_sound;
	static Map<String, Font*> cache_font;
	static Map<String, Atlas*> cache_atlas;

	Renderer* renderer_ref;
public:

	void init(Renderer* ren);

	static Texture* load_texture(String path);
	static Sound* load_sound(String path);
	static Font* load_font(String path);
	static Atlas* load_atlas(String path);


	static const char* get_asset_path(const char* virtualPath);

	static std::string read_file(String filePath);
};