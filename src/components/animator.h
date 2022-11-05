#pragma once

#include <core/types.h>
#include <core/ecs.h>

#include <lib/json.hpp>

class Animator : public Component {

public:
	Animator() = default;
	Animator(String path) {
		auto data = nlohmann::json::parse(path + ".json");
		animTex = new Texture(path + ".png");
	
	}

	Texture* animTex;

	void update() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	void render(Renderer* ren) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

};