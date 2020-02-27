#include "Game.h"

/// <summary>
/// Game()
/// Main Game constructor used to initialise SDL, create a window and initialise SDL_IMG
/// </summary>
Game::Game() :
	m_player1()
{
	ControlComponent* controlComp = new ControlComponent(m_player1, 0);

	srand(time(NULL));
	// Initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initialise SDL" << std::endl;
	}
	

	// Create a Window
	p_window = SDL_CreateWindow("ARGO_TEAMB", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCR_W, SCR_H, SDL_WINDOW_SHOWN );
	// Dion Debug window
	//p_window = SDL_CreateWindow("ARGO_TEAMB", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

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

	
	// Initialise Scenes
	//m_hostGame = new HostingGame();
	m_joinGame = new JoiningGame();

	// debug
	m_currentState = GameStates::MainMenu;
	
	// release m_currentState = GameStates::MainMenu;

	m_menuScene = new MenuScene(p_renderer, &m_currentState, controlComp);
	m_creditsScene = new CreditsScene(p_renderer, &m_currentState, controlComp);
	m_font = new FontObserver(p_renderer);
	m_font->loadFont();

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
			update(timePerFrame/1000.0f);
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
	case GameStates::MainMenu:
		m_menuScene->handleEvents();
		m_currentState = m_menuScene->setNewState();
		m_menuScene->update(dt);
		break;
	case GameStates::Game:
		if (m_gameScene->getGameCount() > 5 || m_gameScene->getGameCount() == -1) {
			m_currentState = GameStates::MainMenu;
		}
		m_gameScene->update(dt);
		break;
	case GameStates::Hosting:
		m_hostGame->update(dt);
		break;
	case GameStates::Joining:
		m_joinGame->update(dt);
		break;
	case GameStates::Credits:
		m_creditsScene->update(dt);
		m_currentState = m_creditsScene->backToMenu();
		break;
	case GameStates::QuitGame:
		m_quit = true;
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

	//SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	SDL_RenderClear(p_renderer);

	switch (m_currentState)
	{
	case GameStates::MainMenu:
		m_menuScene->render(p_renderer);
		break;
	case GameStates::Game:
		if (m_gameScene == NULL) {
			m_gameScene = new GameScene(p_renderer);
		}
		else {
			m_gameScene->render();
		}
		
		break;
	case GameStates::Hosting:
		if (m_hostGame == NULL) {
			m_hostGame = new HostingGame();

		}
		else {
			m_hostGame->draw(m_font,p_renderer);
		}
		break;
	case GameStates::Joining:
		m_joinGame->draw(m_font, p_renderer);
		break;
	case GameStates::Credits:
		m_creditsScene->render(p_renderer);
		break;
	case GameStates::QuitGame:
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