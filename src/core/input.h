/*****************************************************************//**
 * \file   input.h
 * \brief  Input system
 * 
 * \date   January 2023
 *********************************************************************/

#pragma once

#include <glm/fwd.hpp>
#include <core/types.h>

/// <summary>
/// Struct containing mouse data
/// </summary>
struct Mouse
{
	/// <summary>
	/// Left mouse button state
	/// </summary>
	bool LMB;

	/// <summary>
	/// Right mouse button state
	/// </summary>
	bool RMB;

	/// <summary>
	/// Scroll state
	/// </summary>
	float scroll;

	/// <summary>
	/// Mouse position
	/// </summary>
	glm::ivec2 pos;

	Uint32 buttons;
};


/// <summary>
/// Class responsible for input handling through SDL
/// </summary>
class Input
{
public:
	/// <summary>
	/// Return if a key is down 
	/// </summary>
	/// <param name="scanCode">Key to check</param>
	/// <returns></returns>
	static bool key_down(SDL_Scancode scanCode);
	
	/// <summary>
	/// Return if a key is held
	/// </summary>
	/// <param name="scanCode">key to check</param>
	/// <returns></returns>
	static bool key_held(SDL_Scancode scanCode);

	/// <summary>
	/// Return wheel event
	/// </summary>
	/// <returns></returns>
	static SDL_MouseWheelEvent get_wheel();

	/// <summary>
	/// Initialize input system
	/// </summary>
	void init();

	/// <summary>
	/// Update input system
	/// </summary>
	/// <param name="evt">event reference</param>
	void update(SDL_Event& evt);

	/// <summary>
	/// Update mouse wheel
	/// </summary>
	/// <param name="mevt"></param>
	void update_mouse_wheel(SDL_MouseWheelEvent mevt);

	void update_mouse_position(Vec2 pos);
	inline void set_mouse_position_override(bool override) { m_mousePositionOverriden = override; }

	/// <summary>
	/// Check if a mouse button is down
	/// </summary>
	/// <param name="key">mouse btn to check</param>
	/// <returns></returns>
	static bool mouse_down(int key);

	/// <summary>
	/// Check if a mouse button is held
	/// </summary>
	/// <param name="key">mouse btn to check</param>
	/// <returns></returns>
	static bool mouse_held(int key);

	/// <summary>
	/// Get mouse position
	/// </summary>
	/// <returns></returns>
	static Vec2 get_mouse_pos();
private:
	bool m_mousePositionOverriden = false;
};



