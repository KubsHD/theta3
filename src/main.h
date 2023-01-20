#pragma once


/*!
 * \file main.h
 *
 * Main file header
 *
 * \date January 2023
 *
 *
 */


/// <summary>
/// Changes scene to specified class
/// </summary>
/// <typeparam name="T">Scene Class to change  to</typeparam>
template<typename T>
void change_scene();

/// <summary>
/// Returns time since startup (in ms)
/// </summary>
/// <returns></returns>
float get_time();

/// <summary>
/// Returns delta time between frames
/// </summary>
/// <returns></returns>
float get_delta();

/// <summary>
/// Returns global update time scale
/// </summary>
/// <returns></returns>
float get_time_scale();

/// <summary>
/// Sets new update time scale
/// </summary>
/// <param name="t">New time scale</param>
void set_time_scale(float t);
