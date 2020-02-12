#ifndef GAME
#define GAME
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "HealthSystem.h"
#include "ControlSystem.h"
#include "AISystem.h"
#include "RenderSystem.h"
#include "Level.h"
#include "ButtonSystem.h"
#include "CollisionSystem.h"
#include "ComponentsEnum.h"
#include "TrapComponent.h"

#include "Globals.h"
#include <time.h>

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
	Entity m_player;
	Entity m_alien;
	Entity m_dog;
	Entity m_cat;
	
	Entity m_button;
	Entity m_button2;

	Entity m_doorButton;

	Entity m_spike;
	Entity m_spike2;
	Entity m_spike3;


	Entity m_door1;
	Entity m_door2;

	Entity m_goalCheese;
	Entity m_bomb;

	// Systems
	HealthSystem m_healthSystem;
	ControlSystem m_controlSystem;
	AISystem m_aiSystem;
	RenderSystem m_renderSystem;
	Level* tiled_map_level;
	ButtonSystem m_buttonSystem;
	CollisionSystem m_collisionSystem;
	std::vector<Entity> m_goalCheeses;
};
#endif // !GAME
