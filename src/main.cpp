﻿#include <iostream>
#include <SDL.h>
#include <lib/glad/glad.h>

#include <core/network.h>
#include "core/log.h"
#include "core/window.h"
#include "core/input.h"
#include "core/types.h"

#include <glm/gtc/matrix_transform.hpp>

#include "render/Renderer.h"

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



#if WIN
#include <Windows.h>

extern "C" {
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
#endif

void init()
{
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
	
	tex_player = new Texture("data/spr_player.png");
	game_view = new Target();
}

void update(float dt)
{
	float speed = 1.0f;

	if (input.key_held(SDL_SCANCODE_RIGHT))
		pos.x += speed;

	if (input.key_held(SDL_SCANCODE_DOWN))
		pos.y += speed;

		if (input.key_held(SDL_SCANCODE_LEFT))
		pos.x -= speed;

	if (input.key_held(SDL_SCANCODE_UP))
		pos.y -= speed;

	if (input.key_down(SDL_SCANCODE_ESCAPE))
		bRunning = false;
}

void render()
{
	game_view->bind();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, 320, 180);


	ren.draw_tex(tex_player, pos);


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	window.getCurrentSize();
	glViewport(0, 0, 1280, 720);


	glBindTexture(GL_TEXTURE_2D, game_view->texId);
	ren.set_mvp(glm::mat4(1.0f));
	ren.draw_quad();
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

	ren.init();

	while (bRunning)
	{

		while (SDL_PollEvent(&evt) != 0)
		{

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
