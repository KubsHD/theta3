#include "main.h"

#include <iostream>
#include <SDL.h>
#include <lib/glad/glad.h>
#include <lib/imgui/imgui.h>
#include <lib/imgui/imgui_impl_sdl.h>
#include <lib/imgui/imgui_impl_opengl3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include <core/audio.h>
#include <core/network.h>
#include "core/log.h"
#include "core/window.h"
#include "core/input.h"
#include "core/types.h"
#include "core/ecs.h"
#include "core/asset.h"

#include "tools/tool.h"
#include "tools/tool_anim.h"


#include "render/renderer.h"

#include <scenes/scene_game.h>
#include <scenes/scene_menu.h>
#include <scenes/scene_title.h>
#include <scenes/scene_shop_test.h>

#include <components/player.h>
#include <components/wave_system.h>


#include <core/uuid.h>

#if WIN
#include <Windows.h>
#include <scenes/scene_shop_test.h>



extern "C" {
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
#endif

bool bRunning = true;
bool b_show_inspector;
bool b_show_player_info;
bool b_demo_open;


static SDL_GLContext maincontext;

float seconds_elapsed = 0.0f;
float g_time_scale = 1.0;

double dt;

SDL_Event evt;
SDL_Window* win;

Window window;
Renderer ren;
Input input;
Audio audio;
Asset ass;

Scene* current_scene;

Vector<Tool*> tools;

template<typename T>
void change_scene()
{
	// reset camera when changing scene, otherwise it remembers the last one
	ren.set_camera(nullptr);

	if (current_scene)
		current_scene->destroy();

	delete current_scene;
	current_scene = new T();
	current_scene->ren = &ren;
	current_scene->init();
	current_scene->update_collider_list();
}

void init()
{

#pragma region EngineInit

	// Initializing SDL2O
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		log_error("Error: %s", SDL_GetError());
	}


	// Request an OpenGL 4.5 context (should be core)
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Initializing window
	window.create();

	input.init();

	audio.init();

	ass.init(&ren);

	//SDL_GL_MakeCurrent(window.pWindow, maincontext);

	maincontext = SDL_GL_CreateContext(window.pWindow);
	if (maincontext == NULL)
		log_error("Failed to create OpenGL context");

	// Initializing OpenGL
	if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
	{
		std::cout << "Failed to initialize GLAD. " << std::endl;
	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
//io.ConfigViewportsNoTaskBarIcon = true;

// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplSDL2_InitForOpenGL(window.pWindow, maincontext);
	ImGui_ImplOpenGL3_Init();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#pragma endregion

	tools.push_back(new AnimationTool());


	for (auto& tool : tools)
	{
		tool->init();
	}
}

void update(float dt)
{
	if (current_scene != nullptr)
		current_scene->update();
}

void render()
{
	if (current_scene != nullptr)
		current_scene->render();


	{
		for (auto& tool : tools)
		{
			tool->render();
		}
	}

	{
		ImGui::BeginMainMenuBar();

		if (ImGui::BeginMenu("Scenes"))
		{
			if (ImGui::MenuItem("Game"))
				change_scene<GameScene>();


			if (ImGui::MenuItem("Menu"))
				change_scene<MenuScene>();

			if (ImGui::MenuItem("Title"))
				change_scene<TitleScene>();

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Tools"))
		{
			if (ImGui::MenuItem("Inspector"))
			{
				if (current_scene != nullptr)
					b_show_inspector = true;

			}


			if (ImGui::MenuItem("ImGui Demo"))
			{
				b_demo_open = !b_demo_open;
			}

			ImGui::EndMenu();
		}



		if (ImGui::Button("Quit"))
		{
			bRunning = false;
		}


		ImGui::EndMainMenuBar();
	}

	if (b_demo_open)
		ImGui::ShowDemoWindow();

	if (ImGui::Begin("Global settings"))
	{
		float a = get_time_scale();
		ImGui::DragFloat("Time scale", &a, 0.01f, 0.1f, 2.0f);
		set_time_scale(a);
	}
	ImGui::End();

	if (b_show_inspector)
	{
		if (ImGui::Begin("Inspector"))
		{
			ImGui::Text("Entity list");
			for (auto ent : current_scene->get_entities())
			{

				auto str = "Entity " + ent->id + ": " + ent->name;
				if (ImGui::CollapsingHeader(str.c_str(), true))
				{
					ImGui::Text("Position X: %f, Y: %f", ent->position.x, ent->position.y);
					ImGui::Text("Num of components: %d", ent->get_component_count());
				}
			}

		}
			ImGui::End();
	}

	

}

int main(int argc, char* argv[])
{
	srand(time(NULL));

	init();
	// Keeping game running at 60 fps
	float MS = g_time_scale * 16.6666666666667f;
	double last = SDL_GetTicks64();
	double lag = 0.0;
	double current = 0;

	ren.init(&window);

	if (true || argv[1] == "--compile")
	{
		for (auto& path : std::filesystem::recursive_directory_iterator(std::filesystem::path(ass.get_asset_path("anim/"))))
		{
			auto p = path.path();

			if (p.extension().string() == ".json")
			{
				p.replace_extension();
				AtlasData::convert_from_json(p.string());
			}
		}

	}

	change_scene<MenuScene>();

	while (bRunning)
	{
		MS = g_time_scale * 16.6666666666667f;

		while (SDL_PollEvent(&evt) != 0)
		{
			ImGui_ImplSDL2_ProcessEvent(&evt);

			switch (evt.type)
			{
			case SDL_WINDOWEVENT:
				if (evt.window.event == SDL_WINDOWEVENT_CLOSE)
					bRunning = false;

				if (evt.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					window.w = evt.window.data1;
					window.h = evt.window.data2;
					ren.update_size(window.w, window.h);
				}

				break;
			case SDL_MOUSEWHEEL:
				input.update_mouse_wheel(evt.wheel);
				break;
			case SDL_QUIT:
				bRunning = false;
				break;
			}
		}


		current = SDL_GetTicks64();
		dt = current - last;
		last = current;
		lag += dt;

		seconds_elapsed = current / 1000;

		while (lag < MS)
		{
			int milliseconds = (int)(MS - lag);
			SDL_Delay(milliseconds);

			current = SDL_GetTicks64();
			dt = current - last;
			last = current;
			lag += dt;
		}

		while (lag >= MS)
		{
			update(dt);
			lag -= MS;
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport(0, ImGuiDockNodeFlags_PassthruCentralNode);

		render();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
			SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
		}

		SDL_GL_SwapWindow(window.pWindow);


		input.update(evt);
		audio.update();
	}


	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	window.close();
	SDL_Quit();

	return 0;
}

float get_time()
{
	return seconds_elapsed;
}

float get_delta()
{
	return dt;
}

float get_time_scale()
{
	return g_time_scale;
}

void set_time_scale(float t)
{
	g_time_scale = t;
}
