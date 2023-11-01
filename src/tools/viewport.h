#pragma once

#include "tool.h"
#include <core/types.h>
#include <render/Renderer.h>

#include <lib/imgui/imgui.h>

class Viewport : public Tool {

public:
	void init() override
	{

	}


	void render() override
	{
		if (ImGui::Begin("Viewport"))
		{
			auto winSize = ImGui::GetWindowSize();

			float scale = glm::min((float)winSize.x / 1280, (float)winSize.y / 720);

			ImGui::Image((void*)Renderer::Viewport->id, ImVec2(1280 * scale, 720 * scale), ImVec2(0, 1), ImVec2(1, 0));
		}
		ImGui::End();
	}

};