#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <render/renderer.h>
#include <fstream>

#include <lib/json.hpp>

struct AnimFrame {
	int idx;
	
};

struct AnimData {
	String name;
	Vector<Subtexture*> Frames;
};

class Animator : public Component {
private:
	AnimData m_ad;
public:
	Animator() = default;
	Animator(String path) {
		std::ifstream ifs(path + ".json");
		auto data = nlohmann::json::parse(ifs);
		animTex = new Texture(path + ".png");

		for (auto frame : data["frames"])
		{
			m_ad.Frames.push_back( new Subtexture
				{	animTex,
					{ frame["frame"]["x"], frame["frame"]["y"] },
					{ frame["frame"]["w"], frame["frame"]["h"] },
				}
			);
		}
	
	}

	Texture* animTex;

	void update() override
	{
		
	}


	void render(Renderer* ren) override
	{
		ren->draw_subtex(m_ad.Frames[0], entity->position);
	}

};