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
#include "Enums.h"
#include "TestBotBehaviourComponent.h"
#include "TrapComponent.h"
#include "ButtonComponent.h"
#include "PlayerComponent.h"
#include "StateMachineSystem.h"
#include "GameSystem.h"
#include "BombSystem.h"
#include "Globals.h"

#include <time.h>
#include "Observer.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "HostingGame.h"
#include "JoiningGame.h"
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

	//Entity m_button;
	//Entity m_button2;

	//Entity m_doorButton;

	//Entity m_spike;
	//Entity m_spike2;
	//Entity m_spike3;


	//Entity m_door1;
	//Entity m_door2;

	//Entity m_goalCheese;

	//std::vector<Entity> m_bomb;

	//Entity m_gameManager;

	//// Systems
	//HealthSystem m_healthSystem;
	//ControlSystem m_controlSystem;
	//AISystem m_aiSystem;
	//RenderSystem m_renderSystem;
	//Level* tiled_map_level;
	//ButtonSystem m_buttonSystem;
	//CollisionSystem m_collisionSystem;
	//StateMachineSystem* m_stateMachine;
	//std::vector<Entity> m_goalCheeses;
	//AudioObserver* m_observer;
	//BombSystem m_bombSystem;
	//GameSystem m_gameSystem;
	FontObserver* m_font;
	GameStates m_currentState;

	//GameScene* m_gameScene;
	MenuScene* m_menuScene;
	GameScene* m_gameScene;

	HostingGame* m_hostGame;
	JoiningGame* m_joinGame;
	//CreditsScene* m_creditsScene;

};
#endif // !GAME
