#include <iostream>
#include <SDL.h>

#include <core/game.h>

#if WIN
#include <Windows.h>
#include <scenes/scene_shop_test.h>
#include <core/file/atl.h>

extern "C" {
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
#endif


int main(int argc, char* argv[])
{
	srand(time(NULL));


	Game game;
	game.init();

	if (argv[1] == "--compile")
	{
		for (auto& path : std::filesystem::recursive_directory_iterator(std::filesystem::path(game.ass.get_asset_path("anim/"))))
		{
			auto p = path.path();

			if (p.extension().string() == ".json")
			{
				p.replace_extension();
				AtlasData::convert_from_json(p.string());
			}
		}

	}

	game.loop();

	SDL_Quit();

	return 0;
}
