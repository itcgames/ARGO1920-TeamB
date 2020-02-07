#include "Game.h"





/// <summary>
/// Game()
/// Main Game constructor used to initialise SDL, create a window and initialise SDL_IMG
/// </summary>
Game::Game() 
{

	m_user_circle.p = { 100, 100 };
	m_user_circle.r = 42;

	
	// Initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initialise SDL" << std::endl;
	}

	// Create a Window
	p_window = SDL_CreateWindow("ARGO_TEAMB", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);
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
	m_player.addComponent(new ControlComponent(m_player), Components::Controller);

	// Alien
	m_alien.addComponent(new HealthComponent(150), Components::Health);
	m_alien.addComponent(new PositionComponent(200, 200), Components::Position);
	m_alien.addComponent(new RenderComponent("Assets\\Alien.png", 100, 100, p_renderer), Components::Render);
	m_alien.addComponent(new ControlComponent(m_alien), Components::Controller);

	// Dog
	m_dog.addComponent(new HealthComponent(75), Components::Health);
	m_dog.addComponent(new PositionComponent(300, 300), Components::Position);
	m_dog.addComponent(new RenderComponent("Assets\\dog.png", 100, 100, p_renderer), Components::Render);
	m_dog.addComponent(new ControlComponent(m_dog), Components::Controller);

	// Cat
	m_cat.addComponent(new HealthComponent(50), Components::Health);
	m_cat.addComponent(new PositionComponent(400, 400), Components::Position);
	m_cat.addComponent(new ControlComponent(m_cat), Components::Controller);
	m_cat.addComponent(new RenderComponent("Assets\\cat.png", 100, 100, p_renderer), Components::Render);

	/*button test*/
	//Button 1
	m_button.addComponent(new ButtonComponent(true, 1), Components::Button);
	m_button.addComponent(new PositionComponent(50, 50), Components::Position);
	m_button.addComponent(new RenderComponent("Assets\\Button.png", 50, 50, p_renderer), Components::Render);

	//Button 2
	m_button2.addComponent(new ButtonComponent(false, 2), Components::Button);
	m_button2.addComponent(new PositionComponent(150, 50), Components::Position);
	m_button2.addComponent(new RenderComponent("Assets\\Button.png", 50, 50, p_renderer), Components::Render);

	//Trap 1
	m_spike.addComponent(new TrapComponent(false, 1), Components::Traps);
	m_spike.addComponent(new PositionComponent(600,600), Components::Position);
	m_spike.addComponent(new RenderComponent("Assets\\Spike.png", 50, 50, p_renderer), Components::Render);

	//Trap 2
	m_spike.addComponent(new TrapComponent(false, 0), Components::Traps);
	m_spike.addComponent(new PositionComponent(700, 600), Components::Position);
	m_spike.addComponent(new RenderComponent("Assets\\Spike.png", 50, 50, p_renderer), Components::Render);

	//Trap 3
	m_spike3.addComponent(new TrapComponent(true, 2), Components::Traps);
	m_spike3.addComponent(new PositionComponent(800, 600), Components::Position);
	m_spike3.addComponent(new RenderComponent("Assets\\Spike.png", 50, 50, p_renderer), Components::Render);


	// Systems
	//HEALTH All entities
	m_healthSystem.addEntity(m_player);
	m_healthSystem.addEntity(m_alien);
	m_healthSystem.addEntity(m_dog);
	m_healthSystem.addEntity(m_cat);

	//CONTROL Player only
	m_controlSystem.addEntity(m_player);
	m_controlSystem.addEntity(m_alien);
	m_controlSystem.addEntity(m_dog);
	m_controlSystem.addEntity(m_cat);

	//DRAW Draw all of entities
	m_renderSystem.addEntity(m_player);
	m_renderSystem.addEntity(m_alien);
	m_renderSystem.addEntity(m_dog);
	m_renderSystem.addEntity(m_cat);

	const auto MAP_PATH = "Assets/map/test.tmx";
	tiled_map_level = new Level("Test");
	tiled_map_level->load(MAP_PATH, p_renderer);

	//m_renderSystem.addEntity(m_alien);
	//m_renderSystem.addEntity(m_dog);
	//m_renderSystem.addEntity(m_cat);

	m_renderSystem.addEntity(m_button);
	m_renderSystem.addEntity(m_button2);
	m_renderSystem.addEntity(m_spike);
	m_renderSystem.addEntity(m_spike2);
	m_renderSystem.addEntity(m_spike3);

	//Connect button entity and trap entity
	m_trapSystem.addEntity(m_button);
	m_trapSystem.addEntity(m_button2);
	m_trapSystem.addEntity(m_spike);
	m_trapSystem.addEntity(m_spike2);
	m_trapSystem.addEntity(m_spike3);

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
	PositionComponent* c = static_cast<PositionComponent*>(m_player.getComponent(Components::Position));
	std::cout << c->getPositionX() << std::endl;
	std::cout <<  c->getPositionY() << std::endl;


	//if (c2CircletoCircle(user_circle, user_circle)) {
	//	std::cout << " circle to circle" << std::endl;
	//}
	m_healthSystem.update();
	m_aiSystem.update();
	m_trapSystem.update();

	//m_controlSystem.update();
	m_controlSystem.handleInput();
}

/// <summary>
/// render()
/// Method used to render any game objects that have to be drawn
/// </summary>
void Game::render()
{
	SDL_RenderClear(p_renderer);
	tiled_map_level->draw(p_renderer);
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