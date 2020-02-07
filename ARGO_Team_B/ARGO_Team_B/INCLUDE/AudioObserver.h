#ifndef AUDIOOBSERVER_H
#define AUDIOOBSERVER_H
#include "Observer.h"
#include <SDL.h>
#include <SDL_mixer.h>

class AudioObserver :public Observer
{
public:
	enum SoundEffect
	{
		w,
		t,
		f,
	};
	AudioObserver();
	void load();
	//void notify(SoundEffect t_sfx);
	//void playBGM(int t_bgmNum);
private:
	Mix_Chunk * m_w = NULL;
	Mix_Chunk*  m_t = NULL;
	Mix_Chunk*  m_f = NULL;
	Mix_Music * m_wtf = NULL;
};
#endif // !AUDIO_OBSERVER_H

