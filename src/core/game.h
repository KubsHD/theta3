#pragma once

#include <core/types.h>

#include <core/window.h>
#include <core/input.h>
#include <core/audio.h>
#include <render/Renderer.h>
#include <core/asset.h>
#include <core/ecs.h>
#include <system/script_system.h>




class Tool;
class SDL_Window;

class Game {

public:
	Game();

	static Game* Instance;


	/// <summary>
	/// Changes scene to specified class
	/// </summary>
	/// <typeparam name="T">Scene Class to change  to</typeparam>
	template<typename T>
	static void change_scene();

	/// <summary>
	/// Returns time since startup (in ms)
	/// </summary>
	/// <returns></returns>
	static float get_time();

	/// <summary>
	/// Returns delta time between frames
	/// </summary>
	/// <returns></returns>
	static float get_delta();

	/// <summary>
	/// Returns global update time scale
	/// </summary>
	/// <returns></returns>
	static float get_time_scale();

	/// <summary>
	/// Sets new update time scale
	/// </summary>
	/// <param name="t">New time scale</param>
	static void set_time_scale(float t);

	void init();
	void loop();
	

	double dt;

	SDL_Window* win;

	Window window;
	Renderer ren;
	Input input;
	Audio audio;
	Asset ass;

	ScriptSystem script;

private:
	Vector<Tool*> tools;
	Scene* current_scene = nullptr;

	void render();
	void update(float);
};

