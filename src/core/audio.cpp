#include "audio.h"

#include <fmod_errors.h>
#include <fmod.hpp>
#include <core/log.h>

static FMOD::System* sys;

static FMOD_RESULT result;

void Audio::init()
{
	result = FMOD::System_Create(&sys, FMOD_VERSION);

	if (result != FMOD_OK)
	{
		log_error("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}


	result = sys->init(1000, FMOD_INIT_NORMAL, nullptr);

	if (result != FMOD_OK)
	{
		log_error("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}
}

Sound* Audio::create_sound(String path)
{
	Sound* s = new Sound();

	FMOD::Sound* snd;
	result = sys->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &snd);

	if (result != FMOD_OK)
	{
		log_error("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}

	s->path = path;
	s->ptr = snd;

	return s;
}

void Audio::play_one_shot(Sound* snd)
{
	result = sys->playSound(snd->ptr, NULL, 0, &snd->chnl);

	if (result != FMOD_OK)
	{
		log_error("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}
}

