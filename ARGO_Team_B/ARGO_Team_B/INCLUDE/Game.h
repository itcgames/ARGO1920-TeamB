#ifndef GAME
#define GAME

#include <SDL.h>
#include "Enums.h"

#include "HealthSystem.h"
#include "ControlSystem.h"
#include "AISystem.h"
#include "RenderSystem.h"
#include "Level.h"
#include "ButtonSystem.h"
#include "CollisionSystem.h"
#include "TestBotBehaviourComponent.h"
#include "TrapComponent.h"
#include "ButtonComponent.h"
#include "PlayerComponent.h"
#include "StateMachineSystem.h"
#include "GameSystem.h"
#include "BombSystem.h"

#include <time.h>
#include "Observer.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "HostingGame.h"
#include "JoiningGame.h"
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

	// Entities
	Entity m_rat1;
	Entity m_rat4;
	Entity m_rat2;
	Entity m_rat3;

	AudioObserver* m_observer;

	FontObserver* m_font;
	GameStates m_currentState;

	MenuScene* m_menuScene;
	GameScene* m_gameScene;

	HostingGame* m_hostGame;
	JoiningGame* m_joinGame;
	CreditsScene* m_creditsScene;

};
#endif // !GAME
