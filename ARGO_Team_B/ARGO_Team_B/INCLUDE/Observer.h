#pragma once
#include "Observer.h"
#include <map>
#include <SDL.h>
#include <SDL_mixer.h>

class Observer
{
public:
	~Observer() {};
	void onNotify();

private:

};
class AudioObserver : public Observer
{
	public:
		enum SFX
		{
			CLICK, PORTAL, PICKUPCHEESE, PICKUPBOMB,EXPLOSION,PLACEBOMB,OPENDOOR
		};

		AudioObserver() {
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, NULL, 2048) < 0)
			{
				printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			}
			//Allocate 128 channels for a max for 128 audio chunks playing at one time
			Mix_AllocateChannels(128);
		};
		//Load all resources
		void load()
		{
			click = Mix_LoadWAV("Assets/Sfx/click.wav");
			portal = Mix_LoadWAV("Assets/Sfx/porta.ogg");
			pickupCheese = Mix_LoadWAV("Assets/Sfx/pickupCheese.ogg");
			pickupBomb = Mix_LoadWAV("Assets/Sfx/pickupCheese.ogg");
			placeBomb = Mix_LoadWAV("Assets/Sfx/pickupCheese.ogg");
			explosion = Mix_LoadWAV("Assets/Sfx/explosion.wav"); 
			m_bgm1 = Mix_LoadMUS("Assets/Sfx/music.mp3");
			
		}
		//Function to be called when a message is received from the subject
		//\param sfx: Enum of sound effects
		void onNotify(SFX sfx)
		{
			switch (sfx)
			{
			case AudioObserver::CLICK:
				Mix_PlayChannel(-1, click, 0);
				break;
			case AudioObserver::PORTAL:
				Mix_PlayChannel(-1, portal, 0);
				break;
			case AudioObserver::PICKUPCHEESE:
				Mix_PlayChannel(-1, pickupCheese, 0);
				break;
			case AudioObserver::PICKUPBOMB:
				Mix_PlayChannel(-1, pickupBomb, 0);
				break;
			case AudioObserver::EXPLOSION:
				Mix_PlayChannel(-1, explosion, 0);
				break;
			case AudioObserver::PLACEBOMB:
				Mix_PlayChannel(-1, placeBomb, 0);
				break;
			default:
				break;
			}
		}
		void StartBGM(int bgmSong) {
			switch (bgmSong)
			{
			case 0:
				Mix_PlayMusic(m_bgm1, -1);
				break;
			case 1:
				Mix_PlayMusic(m_bgm2, -1);
				break;
			default:
				Mix_PlayMusic(m_bgm1, -1);
			}
		}
private:
	Mix_Chunk* click = NULL;
	Mix_Chunk* portal = NULL;
	Mix_Chunk* pickupCheese = NULL;
	Mix_Chunk* pickupBomb = NULL;
	Mix_Chunk* explosion = NULL;
	Mix_Chunk* placeBomb = NULL;
	Mix_Music* m_bgm1 = NULL;
	Mix_Music* m_bgm2 = NULL;
};

