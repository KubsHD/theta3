#pragma once

#include "tool.h"
#include <core/types.h>
#include <render/Renderer.h>
#include <core/input.h>
#include <lib/imgui/imgui.h>



class Viewport : public Tool {
	Input& input_ref;
public:

	Viewport(Input& input_ref) : input_ref(input_ref) {}

	void init() override
	{
		input_ref.set_mouse_position_override(true);
	}


	void render() override
	{
		if (ImGui::Begin("Viewport"))
		{
			auto winSize = ImGui::GetWindowSize();

			input_ref.update_viewport_size(winSize);

			float scale = glm::min((float)winSize.x / 1280, (float)winSize.y / 720);

			auto screen_pos = ImGui::GetCursorScreenPos();
			ImGui::Image((void*)Renderer::Viewport->id, ImVec2(1280 * scale, 720 * scale), ImVec2(0, 1), ImVec2(1, 0));

			auto mouse_pos = ImGui::GetMousePos();

			//log_info("viewport.h: %d %d\n", (int)(mouse_pos.x - screen_pos.x) , (int)(mouse_pos.y - screen_pos.y));

			input_ref.update_mouse_position(Vec2((int)(mouse_pos.x - screen_pos.x), (int)(mouse_pos.y - screen_pos.y)));
		}
		ImGui::End();
	}

};