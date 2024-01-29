#include "audio.h"

#include <fmod_errors.h>
#include <fmod.h>
#include <core/log.h>
#include <utils/profiler.h>

static FMOD_SYSTEM* sys;

static FMOD_RESULT result;

void fmod_check_for_error(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		log_error("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}
}


void Audio::init()
{
	THETA_PROFILE;

	result = FMOD_System_Create(&sys, FMOD_VERSION);
	fmod_check_for_error(result);


	result = FMOD_System_Init(sys, 1000, FMOD_INIT_NORMAL, nullptr);
	fmod_check_for_error(result);
}

void Audio::update()
{
	result = FMOD_System_Update(sys);
	fmod_check_for_error(result);
}

Sound* Audio::create_sound(String path)
{
	Sound* s = new Sound();

	FMOD_SOUND* snd;

	
	result = FMOD_System_CreateSound(sys, path.c_str(), FMOD_DEFAULT, nullptr, &snd);
	fmod_check_for_error(result);

	s->path = path;
	s->ptr = snd;
	return s;
}

Sound* Audio::create_sound(String path, Vector<char> data)
{
	Sound* s = new Sound();

	FMOD_SOUND* snd;

	// https://github.com/KubsHD/Tortilla/blob/49f4b268899c3f188d096b2ce89d2bc3ecaeade5/Tortilla/engine/core/FmodAudio.cpp#L27
	FMOD_CREATESOUNDEXINFO ex;

	memset(&ex, 0, sizeof(FMOD_CREATESOUNDEXINFO));

	ex.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
	ex.length = data.size();

	result = FMOD_System_CreateSound(sys, data.data(), FMOD_DEFAULT | FMOD_OPENMEMORY, &ex, &snd);
	fmod_check_for_error(result);

	s->path = path;
	s->ptr = snd;
	return s;
}

void Audio::play_one_shot(Sound* snd)
{	
	result = FMOD_System_PlaySound(sys, snd->ptr, NULL, 0, &snd->chnl);
	fmod_check_for_error(result);
}

void Audio::play_one_shot(Sound* snd, float volume)
{
	result = FMOD_System_PlaySound(sys, snd->ptr, NULL, 0, &snd->chnl);
	fmod_check_for_error(result);
	
	result = FMOD_Channel_SetVolume(snd->chnl, volume);
	fmod_check_for_error(result);
}



