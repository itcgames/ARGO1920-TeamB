#pragma once
#include <map>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace std;

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
			CLICK, PORTAL, PICKUPCHEESE, PICKUPBOMB,EXPLOSION,PLACEBOMB,OPENDOOR,YOUWIN,DRAW,WALK
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
			youWin = Mix_LoadWAV("Assets/Sfx/youWin.wav");
			draw = Mix_LoadWAV("Assets/Sfx/Draw.wav");
			
			//Mix_VolumeChunk(explosion, 15);
			m_bgm1 = Mix_LoadMUS("Assets/Sfx/music.mp3");
			m_bgm2 = Mix_LoadMUS("Assets/Sfx/musicMenu.mp3");
			m_bgm3 = Mix_LoadMUS("Assets/Sfx/musicMenu.mp3");
			//Mix_VolumeMusic(60);


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
			case AudioObserver::YOUWIN:
				Mix_PlayChannel(-1, youWin, 0);
				break;
			case AudioObserver::DRAW:
				Mix_PlayChannel(-1, draw, 0);
				break;
			default:
				break;
			}
		}
		void StartBGM(int bgmSong) 
		{
			switch (bgmSong)
			{
			case 1:

				Mix_PlayMusic(m_bgm1, -1);
				break;
			case 2:
				Mix_PlayMusic(m_bgm2, -1);
				break;
			case 3:
				Mix_PlayMusic(m_bgm3, -1);
				break;
			default:
				break;
			}
		}
private:
	Mix_Chunk* click = NULL;
	Mix_Chunk* portal = NULL;
	Mix_Chunk* pickupCheese = NULL;
	Mix_Chunk* pickupBomb = NULL;
	Mix_Chunk* explosion = NULL;
	Mix_Chunk* placeBomb = NULL;
	Mix_Chunk* youWin = NULL;
	Mix_Chunk* draw = NULL;
	Mix_Music* m_bgm1 = NULL;
	Mix_Music* m_bgm2 = NULL;
	Mix_Music* m_bgm3 = NULL;
};


class FontObserver : public Observer {
public:
	enum FontType
	{
		TIMER1,TIMER2,COUNTER,PLAYERTAG
	};

	FontObserver(SDL_Renderer* renderer){
		m_renderer = renderer;
		if (TTF_Init() == -1) {
			printf("TTF_Init: %s\n", TTF_GetError());
			exit(2);
		}
		
	}

	void loadFont() {
		timer1 = TTF_OpenFont("Assets/ttf/timer1.ttf", 28);
		if (timer1 == NULL) {
			cout << "timer.ttf failed to load! " << TTF_GetError() << endl;
		}

		timer2 = TTF_OpenFont("Assets/ttf/timer2.ttf", 28);
		if (timer2 == NULL) {
			cout << "timer.ttf failed to load! " << TTF_GetError() << endl;
		}


		counter = TTF_OpenFont("Assets/ttf/counter.ttf", 28);
		if (counter == NULL) {
			cout << "counter.ttf failed to load! " << TTF_GetError() << endl;
		}

		playerTag = TTF_OpenFont("Assets/ttf/playerTag.ttf", 28);
		if (counter == NULL) {
			cout << "playerTag.ttf failed to load! " << TTF_GetError() << endl;
		}
	}

	void drawText(int x, int y,int width,int height, const char* text,SDL_Color color, FontType type) {
		switch (type)
		{
		case FontObserver::TIMER1:
			surface = TTF_RenderText_Solid(timer1, text, color);
			break;
		case FontObserver::TIMER2:
			surface = TTF_RenderText_Solid(timer2, text, color);
			break;
		case FontObserver::COUNTER:
			surface = TTF_RenderText_Solid(counter, text, color);
			break;
		case FontObserver::PLAYERTAG:
			surface = TTF_RenderText_Solid(playerTag, text, color);
			break;
		default:
			break;
		}
		SDL_Texture* message = SDL_CreateTextureFromSurface(m_renderer, surface);
		SDL_Rect message_rect = { x, y, width, height };
		SDL_RenderCopy(m_renderer, message, NULL, &message_rect);

		// free memory
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(message);
	}
private:

	TTF_Font* timer1 = NULL;
	TTF_Font* timer2 = NULL;
	TTF_Font* counter = NULL;
	TTF_Font* playerTag = NULL;
	SDL_Renderer* m_renderer = NULL;
	SDL_Surface* surface = NULL;
};