#ifndef GAME
#define GAME
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "HealthSystem.h"
#include "ControlSystem.h"
#include "AISystem.h"
#include "RenderSystem.h"
#include "ComponentsEnum.h"

#include <cute_c2.h>

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	int m_unchecked;
	void updateCollider(Entity& t_entity, c2Circle& t_collider);
	bool checkCollision(c2Circle& t_collider, c2Circle& t_otherCollider);
	void handleCollision();

	std::pair<std::vector<c2Circle>, std::vector<bool>> m_colliders;

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

	// Systems
	HealthSystem m_healthSystem;
	ControlSystem m_controlSystem;
	AISystem m_aiSystem;
	RenderSystem m_renderSystem;
};
#endif // !GAME