/*****************************************************************//**
 * \file   audio.h
 * \brief  Audio system
 * 
 * \date   January 2023
 *********************************************************************/

#pragma once

#include <core/types.h>

namespace FMOD {
	class Sound;
	class Channel;
};

/// <summary>
/// Wrapper for the internal fmod data structures
/// </summary>
struct Sound {
	/// <summary>
	/// Pointer to the internal fmod sound
	/// </summary>
	FMOD::Sound* ptr;
	
	/// <summary>
	/// Pointer to the internal fmod channel
	/// </summary>
	FMOD::Channel* chnl;

	/// <summary>
	/// Path to the sound file
	/// </summary>
	String path;
};

/// <summary>
/// Class responsible for audio handling through the FMOD library
/// </summary>
class Audio {
private:
	friend class Asset;

	/// <summary>
	/// Create
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	static Sound* create_sound(String path);
public:
	Audio() {};

	/// <summary>
	/// Initialize audio system
	/// </summary>
	void init();
	
	/// <summary>
	/// Update audio system
	/// </summary>
	void update();
	
	/// <summary>
	/// Play a sound
	/// </summary>
	/// <param name="snd"></param>
	static void play_one_shot(Sound* snd);

	/// <summary>
	/// Play a sound with a volume
	/// </summary>
	/// <param name="snd"></param>
	/// <param name="volume"></param>
	static void play_one_shot(Sound* snd, float volume);
};