#pragma once

#include "tool.h"
#include <components/animator.h>


struct AnimAsset {
	String name;
	Texture* animTex;
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
		}
		ImGui::End();
	}

};