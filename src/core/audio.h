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
private:
	friend class Asset;

	static Sound* create_sound(String path);
public:
	Audio() {};

	void init();
	
	void update();
	
	static void play_one_shot(Sound* snd);
	static void play_one_shot(Sound* snd, float volume);
};