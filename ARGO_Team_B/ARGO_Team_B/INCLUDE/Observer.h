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
			TEST, TEST1, TEST2
		};

		AudioObserver() {};
		//Load all resources
		void load()
		{
			test = Mix_LoadWAV("Assets/Sfx/click.wav");
			test1 = Mix_LoadWAV("Assets/Sfx/click.wav");
			test2 = Mix_LoadWAV("Assets/Sfx/click.wav");
			
		}
		//Function to be called when a message is received from the subject
		//\param sfx: Enum of sound effects
		void onNotify(SFX sfx)
		{
			switch (sfx)
			{
			case AudioObserver::TEST:
				Mix_PlayChannel(-1, test, 0);
				break;
			case AudioObserver::TEST1:
				Mix_PlayChannel(-1, test1, 0);
				break;
			case AudioObserver::TEST2:
				Mix_PlayChannel(-1, test2, 0);
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
	Mix_Chunk* test = NULL;
	Mix_Chunk* test1 = NULL;
	Mix_Chunk* test2 = NULL;
	Mix_Music* m_bgm1 = NULL;
	Mix_Music* m_bgm2 = NULL;
};

