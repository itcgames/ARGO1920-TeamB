#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "HealthSystem.h"
#include "ControlSystem.h"
#include "AISystem.h"
#include "RenderSystem.h"
#include "ButtonSystem.h"

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
	Entity m_trap;
	Entity m_trap2;
	Entity m_trap3;

	// Systems
	HealthSystem m_healthSystem;
	ControlSystem m_controlSystem;
	AISystem m_aiSystem;
	RenderSystem m_renderSystem;

	ButtonSystem m_trapSystem;
};