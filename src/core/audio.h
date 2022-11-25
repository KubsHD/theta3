#pragma once

#include <core/types.h>

namespace FMOD {
	class Sound;
	class Channel;
};

struct Sound {
	FMOD::Sound* ptr;
	FMOD::Channel* chnl;
	String path;
};

class Audio {
public:
	Audio() {};

	void init();
	
	static Sound* create_sound(String path);
	
	static void play_one_shot(Sound* snd);
};