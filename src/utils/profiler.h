#pragma once

#ifdef WIN
#define TRACY_ENABLE
#include <tracy/Tracy.hpp>
#include <lib/glad/glad.h>
#include <tracy/TracyOpenGL.hpp>

#define THETA_PROFILE ZoneScoped
#define THETA_PROFILE_FRAME(x) FrameMark
#define THETA_PROFILE_SECTION(x) ZoneScopedN(x)
#define THETA_PROFILE_TAG(y, x) ZoneText(x, strlen(x))
#define THETA_PROFILE_LOG(text, size) TracyMessage(text, size)
#define THETA_PROFILE_VALUE(text, value) TracyPlot(text, value)
#else
#define THETA_PROFILE 
#define THETA_PROFILE_FRAME(x) 
#define THETA_PROFILE_SECTION(x) 
#define THETA_PROFILE_TAG(y, x)
#define THETA_PROFILE_LOG(text, size)
#define THETA_PROFILE_VALUE(text, value)
#endif