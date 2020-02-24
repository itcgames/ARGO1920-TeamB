#ifndef GAME_SCENE_H
#define GAME_SCENE_H
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
class GameScene
{
public:
	GameScene(SDL_Renderer* t_renderer);
	~GameScene();
	void update(float dt);
	void render();

	/// <summary>
	/// online game only
	/// </summary>
	
	//player transfer data
	SDL_Point playerPosition(int id);
	bool playerGetCheese(int id);

	//game transfer data
	float gameStartCountdown();
	float ingameTimer();
	

private:
	// Entities
	Entity m_rat1;
	Entity m_rat4;
	Entity m_rat2;
	Entity m_rat3;

	Entity m_button;
	Entity m_button2;

	Entity m_doorButton;

	Entity m_spike;
	Entity m_spike2;
	Entity m_spike3;


	Entity m_door1;
	Entity m_door2;

	Entity m_goalCheese;

	Entity m_gameManager;

	// Systems
	HealthSystem m_healthSystem;
	ControlSystem m_controlSystem;
	AISystem m_aiSystem;
	RenderSystem m_renderSystem;
	Level* tiled_map_level;
	ButtonSystem m_buttonSystem;
	CollisionSystem m_collisionSystem;
	StateMachineSystem* m_stateMachine;
	AudioObserver* m_observer;
	FontObserver* m_font;
	BombSystem m_bombSystem;
	GameSystem m_gameSystem;

	SDL_Rect m_view;

	std::vector<ParticleSystem*> m_particles;
	std::vector<Entity> m_goalCheeses;
	std::vector<Entity> m_bombs;
	
	SDL_Renderer* m_renderer;

	float m_restartTimer;
	void resetGame();
};
#endif // !MENU_SCENE_H

