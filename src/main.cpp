﻿#include <iostream>
#include <SDL.h>
#include <lib/glad/glad.h>

#include <core/network.h>
#include "core/log.h"
#include "core/window.h"
#include "core/input.h"
#include "core/types.h"
#include "core/ecs.h"

#include <glm/gtc/matrix_transform.hpp>

#include "render/renderer.h"

#include <components/sprite.h>
#include <components/movement.h>
#include <components/animator.h>

// enemies
#include <components/enemy_adult.h>
#include <components/enemy_child.h>
#include <components/enemy_policeman.h>
#include <components/enemy_soldier.h>



bool bRunning = true;
static SDL_GLContext maincontext;

SDL_Event evt;
SDL_Window* win;

Window window;
Renderer ren;
Input input;

Texture* tex_player;
Vec2 pos;

Target* game_view;

World world;


Ref<Camera> game_camera;

#if WIN
#include <Windows.h>

extern "C" {
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
#endif

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
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG );
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Initializing window
	window.create();

	input.init();

	//SDL_GL_MakeCurrent(window.pWindow, maincontext);

	maincontext = SDL_GL_CreateContext(window.pWindow);
	if (maincontext == NULL)
		log_error("Failed to create OpenGL context");

	// Initializing OpenGL
	if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
	{
		std::cout << "Failed to initialize GLAD. " << std::endl;
	}
	

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	#pragma endregion

	game_view = new Target(1280, 720);
	game_camera = CreateRef<Camera>();

	ren.set_camera(game_camera.get());

	auto player = world.create("Player");
	player->add(Sprite("data/spr_player.png"));
	player->add(PlayerMovement(2.0f));
	
	auto animator = player->add(Animator());
	animator->add_animation("data/anim/anm_witch_atk_R");


	// Enemy Adult
	Entity* adult = world.create("AdultEnemy1");
	adult->add(Adult(player));
	adult->add(Sprite("data/spr_enemy_adult.png"));


	// Enemy Child
	Entity* child = world.create("ChildEnemy1");
	child->add(Child(player));
	child->add(Sprite("data/spr_enemy_child.png"));	

	// Enemy Policeman
	Entity* policeman = world.create("PolicemanEnemy1");
	policeman->add(Policeman(player));
	policeman->add(Sprite("data/spr_enemy_police.png"));


	// Enemy Soldier
	Entity* soldier = world.create("SoldierEnemy1");
	soldier->add(Soldier(player));
	soldier->add(Sprite("data/spr_enemy_soldier.png"));

}

void update(float dt)
{
	world.update();

	float speed = 1.0f;

	if (Input::key_held(SDL_SCANCODE_RIGHT))
		game_camera->position.x += speed;

	if (Input::key_held(SDL_SCANCODE_DOWN))
		game_camera->position.y += speed;

	if (Input::key_held(SDL_SCANCODE_LEFT))
		game_camera->position.x -= speed;

	if (Input::key_held(SDL_SCANCODE_UP))
		game_camera->position.y -= speed;

	if (input.key_down(SDL_SCANCODE_ESCAPE))
		bRunning = false;
}

void render()
{
	ren.set_target(game_view);
	ren.clear();

	
	world.render(&ren);


	ren.set_target(Renderer::Backbuffer);
	ren.clear();

	ren.draw_target(game_view);
}

int main(int argc, char* argv[])
{
	srand(time(NULL));

	init();
	// Keeping game running at 60 fps
	const float MS = 16.6666666666667f;
	double last = SDL_GetTicks64();
	double lag = 0.0;
	double current = 0;

	ren.init(&window);

	while (bRunning)
	{

		while (SDL_PollEvent(&evt) != 0)
		{
			if (evt.type == SDL_QUIT)
				bRunning = false;
		}

		//ImGui_ImplSDL2_ProcessEvent(&event);

		current = SDL_GetTicks64();
		double dt = current - last;
		last = current;
		lag += dt;


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

		render();

		SDL_GL_SwapWindow(window.pWindow);
		


		input.update(evt);
		//audio_update();
	}


	window.close();

	return 0;
}
