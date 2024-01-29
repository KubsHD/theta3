#include <iostream>
#include <SDL.h>

#include <core/game.h>
#include <core/file/atl.h>


#if WIN
#include <Windows.h>
#include <scenes/scene_shop_test.h>

extern "C" {
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
#endif

#include <tools/pak/pak_format.h>
#include <core/log.h>
#include <tools/pak/paker.h>
#include <filesystem>

#include <tools/pak/vfs.h>

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
	//srand(time(NULL));
	if (argc > 1)
	{
		if (strcmp(argv[1], "--cook") == 0)
		{
			if (!fs::is_directory("data") || !fs::exists("data")) { // Check if src folder exists
				fs::create_directory("data"); // create src folder
			}


			log_info("Cooking...");
			cook();
			return 0;
		}
		else {
		

		}
	}

	Game game;
	
	game.init();

	if (argv[1] == "--cook_atlas")
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
