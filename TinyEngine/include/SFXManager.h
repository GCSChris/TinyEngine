#ifndef SFX_MANAGER_H
#define SFX_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string.h>
#include "ResourceManager.h"

/** Manager for Sound Effects and Music */
class SFXManager {
public:

	/** Gets the instance of the SFXManager */
	static SFXManager& instance() {
		if (sfxInstance == nullptr) {
			sfxInstance = new SFXManager();
			if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
			{
				SDL_Log("Error opening mixer in SFXManager");
			}
		}
		return *sfxInstance;
	}

	/** Plays music at the given path */
	void playMusic(/** The path to the song */ std::string song) {
		music = NULL;
		ResourceManager& resourceManager = ResourceManager::instance();
		music = resourceManager.getMusic(song);
		Mix_PlayMusic(music, -1);

	}

	/** Play sound effects at the given path */
	void playSFX(/** The path to the sound effect */std::string sound) {
		ResourceManager& resourceManager = ResourceManager::instance();
		Mix_Chunk* sfx = resourceManager.getSFX(sound);
		Mix_PlayChannel(-1, sfx, 0);
	}

	/** Toggles whether or not the music is playing */
	void toggleMusic() {
		if (Mix_PlayingMusic() == 0)
		{
			//Play the music
			Mix_PlayMusic(music, -1);
		}
		//If music is being played
		else
		{
			//If the music is paused
			if (Mix_PausedMusic() == 1)
			{
				//Resume the music
				Mix_ResumeMusic();
			}
			//If the music is playing
			else
			{
				//Pause the music
				Mix_PauseMusic();
			}
		}
	}

	/** Gets the music's volume */
	int getMusicVolume() {
		return Mix_VolumeMusic(-1); //-1 means getter here
	}

	/** Sets the music volume */
	void setMusicVolume(int vol) {
		Mix_VolumeMusic(vol);
	}

private:
	/** The Private constructor for the SFXManager */
	SFXManager() {}
	/** The Private destructor for the SFXManager */
	~SFXManager() {}

	/** The current instance of the SFXManager */
	static SFXManager* sfxInstance;
	/** The current Mix_Music playing the background music */
	Mix_Music* music;
};

#endif
