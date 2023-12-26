#include "asset.h"

#include <render/Renderer.h>
#include <core/audio.h>
#include <core/log.h>
#include <lib/stb_image.h>

#include <SDL_filesystem.h>

#include <string>
#include <fstream>
#include <iostream>
#include <render/device.h>
#include <utils/file.h>

#include <cassert>

#include <core/file/atl.h>
#include <utils/profiler.h>

static const char* path_prefix;

Map<String, Texture*> Asset::cache_texture;
Map<String, Sound*> Asset::cache_sound;
Map<String, Font*> Asset::cache_font;
Map<String, Atlas*> Asset::cache_atlas;

void Asset::init(Renderer* ren)
{
	THETA_PROFILE;

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


Texture* Asset::load_texture(std::vector<char> data)
{
	THETA_PROFILE;

	Texture* tex;

	// load and generate the texture
	int width, height, nrChannels;

	stbi_uc* dat = (stbi_uc*)data.data();

	stbi_set_flip_vertically_on_load(true);
	unsigned char* img_data = stbi_load_from_memory(dat, data.size(), &width, &height, &nrChannels, 0);

	if (img_data)
	{
		tex = gpu::device->create_texture({ (void*)img_data, width, height});
	}

	stbi_image_free(img_data);

	return tex;
}

Texture* Asset::load_texture(String path)
{
	THETA_PROFILE;
	THETA_PROFILE_TAG("Texture path", path.c_str());


	assert(std::filesystem::exists(get_asset_path(path.c_str())));

	for (auto [k, v] : cache_texture)
	{
		if (k == path)
			return v;
	}

	auto tex = load_texture(utils::file::ReadAllBytes(get_asset_path(path.c_str())));

	cache_texture.emplace(path, tex);
	return tex;
}

Sound* Asset::load_sound(String path)
{
	THETA_PROFILE;
	THETA_PROFILE_TAG("Sound path", path.c_str());

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
	THETA_PROFILE;

	for (auto [k, v] : cache_font)
	{
		if (k == path)
			return v;
	}

	Font* fnt = new Font(get_asset_path(path.c_str()));
	cache_font.emplace(path, fnt);
	return fnt;
}

Atlas* Asset::load_atlas(String path)
{
	THETA_PROFILE;

	for (auto [k, v] : cache_atlas)
	{
		if (k == path)
			return v;
	}

	Atlas* atl = new Atlas(get_asset_path(path.c_str()));
	cache_atlas.emplace(path, atl);

	return atl;
}

Shader* Asset::load_shader(String shader_name)
{
	THETA_PROFILE;

	String vertexShaderSource = Asset::read_file("shader/" + shader_name + ".vs");
	String fragmentShaderSource = Asset::read_file("shader/" + shader_name + ".fs");
	const char* dataVs;
	const char* dataPs;

	dataVs = vertexShaderSource.c_str();
	dataPs = fragmentShaderSource.c_str();

	return gpu::device->create_shader({
		.vs = (char*)dataVs,
		.ps = (char*)dataPs
		});
}

std::string Asset::read_file(String filePath)
{
	THETA_PROFILE;

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
	THETA_PROFILE;

	size_t needed = snprintf(NULL, 0, "%s%s", path_prefix, virtualPath) + 1;

	char* tmp = (char*)calloc(needed, 1);

	snprintf(tmp, needed, "%s%s", path_prefix, virtualPath);

	return tmp;
}
