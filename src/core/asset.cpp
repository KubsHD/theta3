#include "asset.h"

#include <render/Renderer.h>
#include <core/audio.h>
#include <core/log.h>

#include <SDL_filesystem.h>

#include <string>
#include <fstream>
#include <iostream>

static const char* path_prefix;

Map<String, Texture*> Asset::cache_texture;
Map<String, Sound*> Asset::cache_sound;
Map<String, Font*> Asset::cache_font;

void Asset::init(Renderer* ren)
{
#if DEBUG
	log_info("asset: running debug build!");
#if APPLE
	path_prefix = "../data/";
#else
	path_prefix = "../../../data/";
#endif

#else
#if VITA
	path_prefix = "app0:data/";
#elif XBOX
	char* base = SDL_WinRTGetFSPathUTF8(SDL_WINRT_PATH_INSTALLED_LOCATION);
	int size = snprintf(NULL, 0, "%s/data/", base);
	char* buf = malloc(size + 1);
	sprintf(buf, "%s/data/", base);
	path_prefix = buf;
#elif APPLE

	char* base = SDL_GetBasePath();
	int size = snprintf(NULL, 0, "%sdata/", base);
	char* buf = (char*)malloc(size + 1);
	sprintf(buf, "%sdata/", base);
	path_prefix = buf;
#else
	path_prefix = "data/";
#endif

	printf("asset: path: %s\n", path_prefix);

#endif

	renderer_ref = ren;
}

Texture* Asset::load_texture(String path)
{
	for (auto [k, v] : cache_texture)
	{
		if (k == path)
			return v;
	}

	Texture* tex = new Texture(get_asset_path(path.c_str()));
	cache_texture.emplace(path, tex);
	return tex;
}

Sound* Asset::load_sound(String path)
{
	for (auto [k, v] : cache_sound)
	{
		if (k == path)
			return v;
	}

	Sound* snd = Audio::create_sound(get_asset_path(path.c_str()));
	cache_sound.emplace(path, snd);
	return snd;
}

Font* Asset::load_font(String path)
{
	for (auto [k, v] : cache_font)
	{
		if (k == path)
			return v;
	}

	Font* fnt = new Font(get_asset_path(path.c_str()));
	cache_font.emplace(path, fnt);
	return fnt;
}

std::string Asset::read_file(String filePath)
{
	std::string content;

	auto realFilePath = get_asset_path(filePath.c_str());

	std::ifstream fileStream(realFilePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cout << "file not found! " << filePath << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

const char* Asset::get_asset_path(const char* virtualPath)
{
	size_t needed = snprintf(NULL, 0, "%s%s", path_prefix, virtualPath) + 1;

	char* tmp = (char*)calloc(needed, 1);

	snprintf(tmp, needed, "%s%s", path_prefix, virtualPath);

	return tmp;
}
