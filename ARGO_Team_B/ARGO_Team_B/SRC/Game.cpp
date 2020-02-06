#include "../INCLUDE/Game.h"

/// <summary>
/// Game()
/// Main Game constructor used to initialise SDL, create a window and initialise SDL_IMG
/// </summary>
Game::Game()
{
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
	m_player.addComponent(new HealthComponent(100));
	m_player.addComponent(new PositionComponent(100, 100));
	m_player.addComponent(new RenderComponent("Assets\\Player.png", 100, 100, p_renderer));

	// Alien
	m_alien.addComponent(new HealthComponent(150));
	m_alien.addComponent(new PositionComponent(200, 200));
	m_alien.addComponent(new RenderComponent("Assets\\Alien.png", 100, 100, p_renderer));

	// Dog
	m_dog.addComponent(new HealthComponent(75));
	m_dog.addComponent(new PositionComponent(300, 300));
	m_dog.addComponent(new RenderComponent("Assets\\dog.png", 100, 100, p_renderer));

	// Cat
	m_cat.addComponent(new HealthComponent(50));
	m_cat.addComponent(new PositionComponent(400, 400));
	m_cat.addComponent(new RenderComponent("Assets\\cat.png", 100, 100, p_renderer));

	//Button 1
	m_button.addComponent(new ButtonComponent(true,1));
	m_button.addComponent(new PositionComponent(50, 50));
	m_button.addComponent(new RenderComponent("Assets\\cat.png", 50, 50, p_renderer));

	//Button 2
	m_button2.addComponent(new ButtonComponent(true,2));
	m_button2.addComponent(new PositionComponent(150, 50));
	m_button2.addComponent(new RenderComponent("Assets\\cat.png", 50, 50, p_renderer));

	//Trap 1
	m_trap.addComponent(new TrapComponent(false, 1));
	m_trap.addComponent(new PositionComponent(600,600));
	m_trap.addComponent(new RenderComponent("Assets\\dog.png", 50, 50, p_renderer));

	//Trap 2
	m_trap2.addComponent(new TrapComponent(true, 0));
	m_trap2.addComponent(new PositionComponent(700, 600));
	m_trap2.addComponent(new RenderComponent("Assets\\dog.png", 25, 25, p_renderer));

	//Trap 2
	m_trap3.addComponent(new TrapComponent(false, 2));
	m_trap3.addComponent(new PositionComponent(800, 600));
	m_trap3.addComponent(new RenderComponent("Assets\\dog.png", 50, 50, p_renderer));

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
	//m_renderSystem.addEntity(m_alien);
	//m_renderSystem.addEntity(m_dog);
	//m_renderSystem.addEntity(m_cat);

	m_renderSystem.addEntity(m_button);
	m_renderSystem.addEntity(m_button2);
	m_renderSystem.addEntity(m_trap);
	m_renderSystem.addEntity(m_trap2);
	m_renderSystem.addEntity(m_trap3);

	//Connect button entity and trap entity
	m_trapSystem.addEntity(m_button);
	m_trapSystem.addEntity(m_button2);
	m_trapSystem.addEntity(m_trap);
	m_trapSystem.addEntity(m_trap2);
	m_trapSystem.addEntity(m_trap3);
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
			//m_controlSystem.handleInput(event.key.keysym.sym);
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
	m_healthSystem.update();
	m_aiSystem.update();

	m_controlSystem.handleInput();
	m_trapSystem.setStates();
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