#include "AudioObserver.h"

AudioObserver::AudioObserver()
{

}



void AudioObserver::notify()
{
}

void AudioObserver::playBGM()
{
	Mix_PlayMusic(m_wtf, -1);
}

void AudioObserver::playBGM(int t_bgmNum)
{
	switch (t_bgmNum)
	{
	case 0:
		Mix_PlayMusic(m_wtf, -1);
		break;
	case 1:
		Mix_PlayMusic(m_wtf, -1);
		break;
	case 2:
		Mix_PlayMusic(m_wtf, -1);
		break;
	default:
	case 1:
		Mix_PlayMusic(m_wtf, -1);
		break;
	}
}
void AudioObserver::load()
{
	//m_w = Mix_LoadWAV("sssssssssssssss");
	//m_t = Mix_LoadWAV("sssssssssssssss");
	//m_f = Mix_LoadWAV("sssssssssssssss");
	Mix_VolumeChunk(m_w, 42);
	/*m_wtf = Mix_LoadMUS("aaaaaaaaaaaaaaa");*/
	Mix_VolumeMusic(25);
}