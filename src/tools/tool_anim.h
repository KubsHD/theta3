#pragma once

#include "tool.h"
#include <core/types.h>

#include <core/file/atl.h>


class AnimationTool : public Tool {

	AtlasData dat;

	char file_to_open[999];

public:
	void init() override
	{
		
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

		return result;
	}

	void render() override
	{
		if (ImGui::Begin("Atlas Tool"))
		{
			if (ImGui::Button("Save native format"))
			{
				std::ofstream os(dat.name + ".atl", std::ios::binary);
				cereal::BinaryOutputArchive archive(os);

				archive(dat);
			}

			if (ImGui::Button("Load native format"))
			{
				std::ifstream os(std::string(file_to_open) + std::string(".atl"), std::ios::binary);
				cereal::BinaryInputArchive archive(os);

				archive(dat);
			}

			ImGui::InputText("file name in anim", file_to_open, 999);

			if (ImGui::Button("Load raw files"))
			{
				dat.name = Path(std::string(Asset::get_asset_path(file_to_open)) + ".json").filename().stem().string();

				std::ifstream ifs(std::string(Asset::get_asset_path(file_to_open)) + ".json");
				auto data = nlohmann::json::parse(ifs);



				for (auto frame : data["frames"])
				{
					dat.sprites.push_back(AtlasSprite(
						{ frame["frame"]["x"], frame["frame"]["y"] },
						{ frame["frame"]["w"], frame["frame"]["h"] }
					));
				}

				dat.sprites_count = dat.sprites.size();


				dat.tex_data = ReadAllBytes(std::string(Asset::get_asset_path(file_to_open)) + ".png");

			}

		}
		ImGui::End();
	}

};