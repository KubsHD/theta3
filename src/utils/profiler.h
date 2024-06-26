#pragma once

#ifdef WIN && DEBUG
#define TRACY_ENABLE
#include <tracy/Tracy.hpp>
#include <lib/glad/glad.h>
#include <tracy/TracyOpenGL.hpp>

#define THETA_PROFILE ZoneScoped
#define THETA_PROFILE_FRAME(x) FrameMark

// this causes memory leak for some reason
// fix later
#define THETA_PROFILE_SECTION(x) ZoneScopedN(x)

#define THETA_PROFILE_TAG(y, x) ZoneText(x, strlen(x))
#define THETA_PROFILE_LOG(text, size) TracyMessage(text, size)
#define THETA_PROFILE_VALUE(text, value) TracyPlot(text, value)
#define THETA_MARK_GPU_CONTEXT TracyGpuContext
#define THETA_GPU_COLLECT TracyGpuCollect
#else
#define THETA_PROFILE 
#define THETA_PROFILE_FRAME(x) 
#define THETA_PROFILE_SECTION(x) 
#define THETA_PROFILE_TAG(y, x)
#define THETA_PROFILE_LOG(text, size)
#define THETA_PROFILE_VALUE(text, value)
#define THETA_MARK_GPU_CONTEXT
#define THETA_GPU_COLLECT
#endif