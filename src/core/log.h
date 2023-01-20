/*****************************************************************//**
 * \file   log.h
 * \brief  Functions responsible for logging
 * 
 * \date   January 2023
 *********************************************************************/


#pragma once

/// <summary>
/// Log info to console
/// </summary>
/// <param name="str">String to print</param>
/// <param name=""></param>
void log_info(const char* str, ...);



/// <summary>
/// Log error to console
/// </summary>
/// <param name="str">Strint to print</param>
/// <param name=""></param>
void log_error(const char* str, ...);
