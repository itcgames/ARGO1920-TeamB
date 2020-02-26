#ifndef GAME_SCENE_H
#define GAME_SCENE_H
#include <SDL.h>

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

#include "FactoryInterface.h"
#include "EntityFactory.h"
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
	string playerInfo(int id);

	//game transfer data
	float gameStartCountdown();
	float ingameTimer();

	void setDataToPlayer(vector<int> player);

private:
	std::vector<Entity*> m_entities;

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
	
	SDL_Renderer* m_renderer;

	float m_restartTimer;
	void resetGame();
};

#endif // !MENU_SCENE_H