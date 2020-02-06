#define CUTE_C2_IMPLEMENTATION
#include "Game.h"


/// <summary>
/// Game()
/// Main Game constructor used to initialise SDL, create a window and initialise SDL_IMG
/// </summary>
Game::Game() :
	m_unchecked{ 0 }
{
	m_colliders.first.reserve(4);
	for (int i = 0; i < m_colliders.first.capacity(); i ++) {
		m_colliders.first.push_back(c2Circle());
		m_colliders.first.back().p = { -100, -100 };
		m_colliders.first.back().r = 42.0f;
		m_colliders.second.push_back(false);
	}

	// Initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initialise SDL" << std::endl;
	}

	// Create a Window
	p_window = SDL_CreateWindow("ARGO_TEAMB", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1080, 720, SDL_WINDOW_SHOWN);
	if (NULL == p_window)
	{
		std::cout << "Error: Could not create window" << std::endl;
	}

	// Create a Renderer
	p_renderer = SDL_CreateRenderer(p_window, -1, 0);
	if (NULL == p_renderer)
	{
		std::cout << "Error: Could not create renderer" << std::endl;
	}

	// Initialise SDL_IMG
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		std::cout << "Failed to initialise IMG" << std::endl;
	}
	SDL_SetRenderDrawColor(p_renderer, 150, 150, 150, 255); // Black Opaque Background

	// Initialise Game Variables

	// Extra info for systems

	// Player
	m_player.addComponent(new HealthComponent(100), Components::Health);
	m_player.addComponent(new PositionComponent(100, 100), Components::Position);
	m_player.addComponent(new RenderComponent("Assets\\Player.png", 100, 100, p_renderer), Components::Render);

	// Alien
	m_alien.addComponent(new HealthComponent(150), Components::Health);
	m_alien.addComponent(new PositionComponent(200, 200), Components::Position);
	m_alien.addComponent(new RenderComponent("Assets\\Alien.png", 100, 100, p_renderer), Components::Render);

	// Dog
	m_dog.addComponent(new HealthComponent(75), Components::Health);
	m_dog.addComponent(new PositionComponent(300, 300), Components::Position);
	m_dog.addComponent(new RenderComponent("Assets\\dog.png", 100, 100, p_renderer), Components::Render);

	// Cat
	m_cat.addComponent(new HealthComponent(50), Components::Health);
	m_cat.addComponent(new PositionComponent(400, 400), Components::Position);
	m_cat.addComponent(new RenderComponent("Assets\\cat.png", 100, 100, p_renderer), Components::Render);

	// Systems
	//HEALTH All entities
	m_healthSystem.addEntity(m_player);
	m_healthSystem.addEntity(m_alien);
	m_healthSystem.addEntity(m_dog);
	m_healthSystem.addEntity(m_cat);

	//CONTROL Player only
	m_controlSystem.addEntity(m_player);

	//AI Everyone except player
	m_aiSystem.addEntity(m_alien);
	m_aiSystem.addEntity(m_dog);
	m_aiSystem.addEntity(m_cat);

	//DRAW Draw all of entities
	m_renderSystem.addEntity(m_player);
	m_renderSystem.addEntity(m_alien);
	m_renderSystem.addEntity(m_dog);
	m_renderSystem.addEntity(m_cat);
}

/// <summary>
/// ~Game()
/// Destructor function for the Game class
/// </summary>
Game::~Game() {}

/// <summary>
/// run()
/// Main game loop for the game, runs methods for updating, rendering and event handling
/// </summary>
void Game::run()
{
	bool exit = false;
	float timePerFrame = 1000.f / 60.f;
	Uint32 timeSinceLastUpdate = 0;
	Uint32 timeSinceStart = SDL_GetTicks();
	while (!m_quit)
	{
		processEvents();
		timeSinceLastUpdate += SDL_GetTicks() - timeSinceStart;
		timeSinceStart = SDL_GetTicks();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
	quit();
}

void Game::updateCollider(Entity& t_entity, c2Circle& t_collider)
{
	PositionComponent* entityPos = static_cast<PositionComponent*>(t_entity.getComponent(Components::Position));
	t_collider.p = c2v{ entityPos->getPositionX(), entityPos->getPositionY() };
}

bool Game::checkCollision(c2Circle& t_collider, c2Circle& t_otherCollider)
{
	bool result = false;
	if (c2CircletoCircle(t_collider, t_otherCollider)) {
		std::cout << "Collision" << std::endl;
		result = true;
	}
	return result;
}

void Game::handleCollision()
{
	// std::cout << "Handle collision here..";
}

/// <summary>
/// processEvents()
/// Method used to poll events in SDL such as keyboard events or window close events
/// </summary>
void Game::processEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.key.keysym.sym == SDLK_ESCAPE) 
		{
			m_quit = true;
		}
		switch (event.type)
		{
		case SDL_KEYDOWN:
			m_controlSystem.handleInput(event.key.keysym.sym);
			break;
		case SDL_QUIT:
			m_quit = true;
			break;
		}
	}
}

/// <summary>
/// update(float dt)
/// Method used to update game objects and attributes
/// </summary>
/// <param name="dt">The time that has passed since the last update call in seconds</param>
void Game::update(float dt)
{

	updateCollider(m_player, m_colliders.first.at(0));
	updateCollider(m_alien, m_colliders.first.at(1));
	updateCollider(m_dog, m_colliders.first.at(2));
	updateCollider(m_cat, m_colliders.first.at(3));

	for (int i = 0; i < m_colliders.first.size(); i++) {
		m_colliders.second.at(i) = false;
	}
	for (int i = 0; i < m_colliders.first.size(); i++) {
		if (!m_colliders.second.at(i))
		{
			m_unchecked = i;
		}
		for (m_unchecked; m_unchecked < m_colliders.first.size(); m_unchecked++) {
			{
				if (i != m_unchecked) {
					if (checkCollision(m_colliders.first.at(i), m_colliders.first.at(m_unchecked))) {
						handleCollision();
					}
					m_colliders.second.at(i) = true;
				}
			}
		}
	}

	m_healthSystem.update();
	m_aiSystem.update();

	m_controlSystem.handleInput();
}

/// <summary>
/// render()
/// Method used to render any game objects that have to be drawn
/// </summary>
void Game::render()
{
	SDL_RenderClear(p_renderer);
	m_renderSystem.draw();
	SDL_RenderPresent(p_renderer);
}

/// <summary>
/// quit()
/// Method used to appropriately end use of the SDL and SDL_IMG libraries
/// </summary>
void Game::quit()
{
	SDL_DestroyRenderer(p_renderer);
	SDL_DestroyWindow(p_window);
	IMG_Quit();
	SDL_Quit();
}