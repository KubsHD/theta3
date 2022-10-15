#include "fmod.h"

const char* FMOD_ErrorString(FMOD_RESULT errcode)
{
	return "unimplemented";
}

FMOD_RESULT FMOD_System_Create(FMOD_SYSTEM** system, unsigned int headerversion)
{
	return FMOD_OK;
}

FMOD_RESULT FMOD_System_PlaySound(FMOD_SYSTEM* system, FMOD_SOUND* sound, FMOD_CHANNELGROUP* channelgroup, FMOD_BOOL paused, FMOD_CHANNEL** channel)
{
return FMOD_OK;
}

FMOD_RESULT FMOD_System_Init(FMOD_SYSTEM* system, int maxchannels, FMOD_INITFLAGS flags, void* extradriverdata)
{
return FMOD_OK;
}

FMOD_RESULT FMOD_System_Close(FMOD_SYSTEM* system)
{
return FMOD_OK;
}

FMOD_RESULT FMOD_System_GetSoftwareFormat(FMOD_SYSTEM* system, int* samplerate, FMOD_SPEAKERMODE* speakermode, int* numrawspeakers)
{
return FMOD_OK;
}

FMOD_RESULT FMOD_Sound_SetLoopCount(FMOD_SOUND* sound, int loopcount)
{
return FMOD_OK;
}

FMOD_RESULT FMOD_Channel_SetVolume(FMOD_CHANNEL* channel, float volume)
{
return FMOD_OK;
}

FMOD_RESULT FMOD_Channel_GetDSPClock(FMOD_CHANNEL* channel, unsigned long long* dspclock, unsigned long long* parentclock)
{
return FMOD_OK;
}

FMOD_RESULT FMOD_Channel_SetDelay(FMOD_CHANNEL* channel, unsigned long long dspclock_start, unsigned long long dspclock_end, FMOD_BOOL stopchannels)
{
return FMOD_OK;
}

FMOD_RESULT FMOD_Channel_GetDelay(FMOD_CHANNEL* channel, unsigned long long* dspclock_start, unsigned long long* dspclock_end, FMOD_BOOL* stopchannels)
{
return FMOD_OK;
}

FMOD_RESULT FMOD_Channel_AddFadePoint(FMOD_CHANNEL* channel, unsigned long long dspclock, float volume)
{
return FMOD_OK;
}

FMOD_RESULT FMOD_System_Update(FMOD_SYSTEM* system)
{
return FMOD_OK;
}

FMOD_RESULT FMOD_System_CreateSound(FMOD_SYSTEM* system, const char* name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO* exinfo, FMOD_SOUND** sound)
{
return FMOD_OK;
}

FMOD_RESULT FMOD_System_GetMasterChannelGroup(FMOD_SYSTEM* system, FMOD_CHANNELGROUP** channelgroup)
{
return FMOD_OK;
}

FMOD_RESULT FMOD_ChannelGroup_SetVolume(FMOD_CHANNELGROUP* channelgroup, float volume)
{
return FMOD_OK;
}

