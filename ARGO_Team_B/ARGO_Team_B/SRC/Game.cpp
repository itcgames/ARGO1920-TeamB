#include "Game.h"

/// <summary>
/// Game()
/// Main Game constructor used to initialise SDL, create a window and initialise SDL_IMG
/// </summary>
Game::Game()
{
	srand(time(NULL));
	// Initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initialise SDL" << std::endl;
	}

	// Create a Window
	p_window = SDL_CreateWindow("ARGO_TEAMB", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCR_W, SCR_H, SDL_WINDOW_SHOWN);
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

	//Allocate 128 channels for a max for 128 audio chunks playing at one time
	Mix_AllocateChannels(128);

	// Initialise Game Variables

	// Extra info for systems
	m_gameScene = new GameScene(p_renderer);
	
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
			update(timePerFrame / 1000.0f);
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
	switch (m_currentState)
	{
	case GameStates::Game:
		m_gameScene->update(dt);
		break;
	case GameStates::MainMenu:
		break;
	case GameStates::Credits:
		break;
	default:
		break;
	}

}

/// <summary>
/// render()
/// Method used to render any game objects that have to be drawn
/// </summary>
void Game::render()
{
	SDL_RenderClear(p_renderer);
	switch (m_currentState)
	{
	case GameStates::Game:
		m_gameScene->render(p_renderer);
		break;
	case GameStates::MainMenu:
		break;
	case GameStates::Credits:
		break;
	default:
		break;
	}

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