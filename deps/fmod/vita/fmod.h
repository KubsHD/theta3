#pragma once

#define FMOD_VERSION 2137

typedef enum
{
	FMOD_OK,
} FMOD_RESULT;

typedef enum
{
	FMOD_DEFAULT,
	FMOD_INIT_NORMAL
} FmodInitStates;

typedef enum
{
	FMOD_SPEAKERMODE_DEFAULT
} FMOD_SPEAKERMODE;

typedef struct
{
	int a;
} FMOD_SOUND;

typedef struct
{
	int a;
} FMOD_SYSTEM;

typedef struct
{
	int a;
} FMOD_CHANNEL;

typedef struct
{
	int a;
} FMOD_CHANNELGROUP;

typedef struct FMOD_CREATESOUNDEXINFO
{

} FMOD_CREATESOUNDEXINFO;

typedef int FMOD_BOOL;
typedef unsigned int FMOD_MODE;
typedef unsigned int FMOD_INITFLAGS;

const char* FMOD_ErrorString(FMOD_RESULT res);

/* Init/Close. */

FMOD_RESULT  FMOD_System_Create(FMOD_SYSTEM** system, unsigned int headerversion);

FMOD_RESULT  FMOD_System_PlaySound(FMOD_SYSTEM* system, FMOD_SOUND* sound, FMOD_CHANNELGROUP* channelgroup, FMOD_BOOL paused, FMOD_CHANNEL** channel);

FMOD_RESULT  FMOD_System_Init(FMOD_SYSTEM* system, int maxchannels, FMOD_INITFLAGS flags, void* extradriverdata);
FMOD_RESULT  FMOD_System_Close(FMOD_SYSTEM* system);
FMOD_RESULT  FMOD_System_GetSoftwareFormat(FMOD_SYSTEM* system, int* samplerate, FMOD_SPEAKERMODE* speakermode, int* numrawspeakers);
FMOD_RESULT  FMOD_System_Update(FMOD_SYSTEM* system);
FMOD_RESULT  FMOD_System_CreateSound(FMOD_SYSTEM* system, const char* name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO* exinfo, FMOD_SOUND** sound);
FMOD_RESULT  FMOD_System_GetMasterChannelGroup(FMOD_SYSTEM* system, FMOD_CHANNELGROUP** channelgroup);

FMOD_RESULT  FMOD_ChannelGroup_SetVolume(FMOD_CHANNELGROUP* channelgroup, float volume);

FMOD_RESULT  FMOD_Sound_SetLoopCount(FMOD_SOUND* sound, int loopcount);

FMOD_RESULT  FMOD_Channel_SetVolume(FMOD_CHANNEL* channel, float volume);
FMOD_RESULT  FMOD_Channel_GetDSPClock(FMOD_CHANNEL* channel, unsigned long long* dspclock, unsigned long long* parentclock);
FMOD_RESULT  FMOD_Channel_SetDelay(FMOD_CHANNEL* channel, unsigned long long dspclock_start, unsigned long long dspclock_end, FMOD_BOOL stopchannels);
FMOD_RESULT  FMOD_Channel_GetDelay(FMOD_CHANNEL* channel, unsigned long long* dspclock_start, unsigned long long* dspclock_end, FMOD_BOOL* stopchannels);
FMOD_RESULT  FMOD_Channel_AddFadePoint(FMOD_CHANNEL* channel, unsigned long long dspclock, float volume);
