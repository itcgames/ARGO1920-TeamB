#include "AudioObserver.h"

AudioObserver::AudioObserver()
{

}



//void AudioObserver::notify(SoundEffect t_sfx)
//{
//	switch (t_sfx)
//	{
//	case AudioObserver::w:
//		Mix_PlayChannel(-1, m_w, 0);
//		break;
//	case AudioObserver::t:
//		Mix_PlayChannel(-1, m_t, 0);
//		break;
//	case AudioObserver::f:
//		Mix_PlayChannel(-1, m_f, 0);
//		break;
//	default:
//		break;
//	}
//}

//void AudioObserver::playBGM()
//{
//	Mix_PlayMusic(m_wtf, -1);
//}

//void AudioObserver::playBGM(int t_bgmNum)
//{
//	switch (t_bgmNum)
//	{
//	case 0:
//		Mix_PlayMusic(m_wtf, -1);
//		break;
//	case 1:
//		Mix_PlayMusic(m_wtf, -1);
//		break;
//	case 2:
//		Mix_PlayMusic(m_wtf, -1);
//		break;
//	default:
//		break;
//	}
//}
void AudioObserver::load()
{
	m_w = Mix_LoadWAV("sssssssssssssss");
	m_t = Mix_LoadWAV("sssssssssssssss");
	m_f = Mix_LoadWAV("sssssssssssssss");
	Mix_VolumeChunk(m_w, 42);
	m_wtf = Mix_LoadMUS("aaaaaaaaaaaaaaa");
	Mix_VolumeMusic(25);
}