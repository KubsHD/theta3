#pragma once

/// Logs provided message with lowest severity
/// @param str Message to print
void log_info(const char* str, ...);

/// Logs provided message with highest severity
/// @param str Message to print
void log_error(const char* str, ...);