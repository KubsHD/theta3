// dear imgui: Renderer Backend for SDL_Renderer
// (Requires: SDL 2.0.17+)

// Important to understand: SDL_Renderer is an _optional_ component of SDL.
// For a multi-platform app consider using e.g. SDL+DirectX on Windows and SDL+OpenGL on Linux/OSX.
// If your application will want to render any non trivial amount of graphics other than UI,
// please be aware that SDL_Renderer offers a limited graphic API to the end-user and it might
// be difficult to step out of those boundaries.
// However, we understand it is a convenient choice to get an app started easily.

// Implemented features:
//  [X] Renderer: User texture binding. Use 'SDL_Texture*' as ImTextureID. Read the FAQ about ImTextureID!
//  [X] Renderer: Support for large meshes (64k+ vertices) with 16-bit indices.

#pragma once
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "imgui.h"

#include <stddef.h>
#include <assert.h>
#include <stdbool.h>

#define IM_OFFSETOF(_TYPE,_MEMBER)  offsetof(_TYPE, _MEMBER)
#define IM_ASSERT(_EXPR)            assert(_EXPR)     

#include <SDL.h>

IMGUI_API bool     ImGui_ImplSDLRenderer_Init(SDL_Renderer* renderer);
IMGUI_API void     ImGui_ImplSDLRenderer_Shutdown();
IMGUI_API void     ImGui_ImplSDLRenderer_NewFrame();
IMGUI_API void     ImGui_ImplSDLRenderer_RenderDrawData(ImDrawData* draw_data);

// Called by Init/NewFrame/Shutdown
IMGUI_API bool     ImGui_ImplSDLRenderer_CreateFontsTexture();
IMGUI_API void     ImGui_ImplSDLRenderer_DestroyFontsTexture();
IMGUI_API bool     ImGui_ImplSDLRenderer_CreateDeviceObjects();
IMGUI_API void     ImGui_ImplSDLRenderer_DestroyDeviceObjects();
