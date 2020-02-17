#ifndef GAME
#define GAME

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "GameScene.h"
#include "MenuScene.h"
#include "CreditsScene.h"
class Game
{
public:
	Game();
	~Game();
	void run();
private:
	void processEvents();
	void update(float dt);
	void render();
	void quit();

	SDL_Window* p_window;
	SDL_Renderer* p_renderer;
	bool m_quit = false;

	GameStates m_currentState = GameStates::Game;
	GameScene* m_gameScene;
	MenuScene* m_menuScene;
	CreditsScene* m_creditsScene;
	
};
#endif // !GAME
