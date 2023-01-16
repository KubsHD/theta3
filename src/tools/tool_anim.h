#pragma once

#include "tool.h"
#include <components/animator.h>

#include <core/types.h>

#include <cereal/types/unordered_map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>

#include <lib/igfiledialog/ImGuiFileDialog.h>

struct AtlasSprite {

};

struct AtlasData {
	String name;
	Vector<char> tex_data;
	uint32_t tex_data_size;

	Vector<AtlasSprite> sprites;
	uint32_t sprites_count;

	template <class Archive>
	void serialize(Archive& ar)
	{
		ar(name, tex_data, tex_data_size, sprites, sprites_count);
	}
};

class AnimationTool : public Tool {

	AnimData* dat;

public:
	void init() override
	{
		
	}

	void render() override
	{
		if (ImGui::Begin("Animation Tool"))
		{
			if (ImGui::Button("test_save"))
			{
				std::ofstream os("out.cereal", std::ios::binary);
				cereal::BinaryOutputArchive archive(os);

				AtlasData myData;
				archive(myData);
			}

			if (ImGui::Button("test_load"))
			{
				std::ofstream os("out.cereal", std::ios::binary);
				cereal::BinaryOutputArchive archive(os);

				AtlasData myData;
				archive(myData);
			}

		}
		ImGui::End();
	}

};