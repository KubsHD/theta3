/*****************************************************************//**
 * \file   window.h
 * \brief  Window handler
 * 
 * \date   January 2023
 *********************************************************************/

#pragma once
#include <SDL.h>
#include <iostream>
#include <lib/stb_image.h>

/// <summary>
/// Manages main window
/// </summary>
class Window {
public:
	int x, y, w, h;

	/// <summary>
	/// Fullscreen flag
	/// </summary>
	bool fullscreen;
	/// <summary>
	/// Quit flag
	/// </summary>
	bool quit;

	/// <summary>
	/// Window pointer
	/// </summary>
	SDL_Window* pWindow;

	/// <summary>
	/// Window surface
	/// </summary>
	SDL_Surface* pSurface;

	Window();

	/// <summary>
	/// Create window
	/// </summary>
	void create();

	/// <summary>
	/// Close window
	/// </summary>
	void close();

	/// <summary>
	/// Get current window size
	/// </summary>
	void getCurrentSize();
};