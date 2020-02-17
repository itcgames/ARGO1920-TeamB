#pragma once
#include "Observer.h"
#include <map>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

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

		AudioObserver() {};
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


class FontObserver : public Observer {
public:
	enum FontType
	{
		TIMER,COUNTER 
	};

	FontObserver(SDL_Renderer* renderer){
		m_renderer = renderer;
		if (TTF_Init() == -1) {
			printf("TTF_Init: %s\n", TTF_GetError());
			exit(2);
		}
		
	}

	void loadFont() {
		timer = TTF_OpenFont("Assets/ttf/timer2.ttf", 28);
		if (timer == NULL) {
			cout << "timer.ttf failed to load! " << TTF_GetError() << endl;
		}

		counter = TTF_OpenFont("Assets/ttf/counter.ttf", 28);
		if (counter == NULL) {
			cout << "counter.ttf failed to load! " << TTF_GetError() << endl;
		}
	}

	void drawText(int x, int y,int width,int height, const char* text,SDL_Color color, FontType type) {
		switch (type)
		{
		case FontObserver::TIMER:
			surface = TTF_RenderText_Solid(timer, text, color);
			break;
		case FontObserver::COUNTER:
			surface = TTF_RenderText_Solid(counter, text, color);
			break;
		default:
			break;
		}
		SDL_Texture* message = SDL_CreateTextureFromSurface(m_renderer, surface);
		SDL_Rect message_rect = { x, y, width, height };
		SDL_RenderCopy(m_renderer, message, NULL, &message_rect);
	}
private:

	TTF_Font* timer = NULL;
	TTF_Font* counter = NULL;
	SDL_Renderer* m_renderer = NULL;
	SDL_Surface* surface = NULL;
};