#include "Game.h"

/// <summary>
/// Game()
/// Main Game constructor used to initialise SDL, create a window and initialise SDL_IMG
/// </summary>
Game::Game() :
	m_rat1(EntityType::Rat), m_rat2(EntityType::Rat), m_rat3(EntityType::Rat), m_rat4(EntityType::Rat)
{
	ControlComponent* controlComp = new ControlComponent(m_rat1, 0);

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

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, NULL, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}
	//Allocate 128 channels for a max for 128 audio chunks playing at one time
	Mix_AllocateChannels(128);

//	// Initialise Game Variables
//	m_stateMachine = new StateMachineSystem;
//
//	// Extra info for systems
//
//	/// <summary>
//	/// FOR ALL ENTITY
//	/// the position component must create before the collision component
//	/// </summary>
//	// Player
//	m_rat1.addComponent(new PlayerComponent(1), Types::Player); // This must allways be first added
//	m_rat1.addComponent(new HealthComponent(100), Types::Health);
//	m_rat1.addComponent(new PositionComponent(150, 100), Types::Position);
//	m_rat1.addComponent(new CollisionComponent(m_rat1, 30.0f, RAT_H, RAT_W), Types::Collider);
//	m_rat1.addComponent(new ControlComponent(m_rat1), Types::Control);
//	m_rat1.addComponent(new AnimatedSpriteComponent("./Assets/SpriteSheetIdleMouse.png", RAT_H, RAT_W, 5, 5000, p_renderer), Types::AnimatedSprite);
//	//m_rat1.addComponent(new RenderComponent("./Assets/rat.png", RAT_W, RAT_H, RAT_W, RAT_H, p_renderer), Types::Render);
//
//	// Alien
//	m_rat4.addComponent(new PlayerComponent(2), Types::Player); // This must allways be first added
//	m_rat4.addComponent(new HealthComponent(150), Types::Health);
//	m_rat4.addComponent(new PositionComponent(50, 300), Types::Position);
//	m_rat4.addComponent(new CollisionComponent(m_rat4, RAT_W, RAT_H), Types::Collider);
//	m_rat4.addComponent(new ControlComponent(m_rat4), Types::Control);
//	m_rat4.addComponent(new AnimatedSpriteComponent("./Assets/SpriteSheetIdleMouse.png", RAT_H, RAT_W, 5, 5000, p_renderer), Types::AnimatedSprite);
//
//	// Dog
//	m_rat2.addComponent(new PlayerComponent(3), Types::Player); // This must allways be first added
//	m_rat2.addComponent(new HealthComponent(75), Types::Health);
//	m_rat2.addComponent(new PositionComponent(50, 700), Types::Position);
//	m_rat2.addComponent(new CollisionComponent(m_rat2, RAT_W, RAT_H), Types::Collider);
//	m_rat2.addComponent(new ControlComponent(m_rat2), Types::Control);
//	//m_rat2.addComponent(new RenderComponent("./Assets/rat3.png", RAT_W, RAT_H, p_renderer), Types::Render);
//	m_rat2.addComponent(new AnimatedSpriteComponent("./Assets/SpriteSheetIdleMouse.png", RAT_H, RAT_W, 5, 5000, p_renderer), Types::AnimatedSprite);
//
//	// Cat
//	m_rat3.addComponent(new PlayerComponent(4), Types::Player); // This must allways be first added
//	m_rat3.addComponent(new HealthComponent(50), Types::Health);
//	m_rat3.addComponent(new PositionComponent(50, 900), Types::Position);
//	m_rat3.addComponent(new CollisionComponent(m_rat3, RAT_W, RAT_H), Types::Collider);
//	m_rat3.addComponent(new ControlComponent(m_rat3), Types::Control);
//	//m_rat3.addComponent(new RenderComponent("./Assets/rat4.png", RAT_W, RAT_H, p_renderer), Types::Render);
//	m_rat3.addComponent(new AnimatedSpriteComponent("./Assets/SpriteSheetIdleMouse.png", RAT_H, RAT_W, 5, 5000, p_renderer), Types::AnimatedSprite);
//	m_rat3.addComponent(new TestBotBehaviourComponent(m_rat3), Types::TestBot);
//
//	/*button test*/
//	//Button 1
//	m_button.addComponent(new ButtonComponent(false, 1, 1), Types::Button);
//	m_button.addComponent(new PositionComponent(600, 50), Types::Position);
//	m_button.addComponent(new CollisionComponent(m_button, 30, 30), Types::Collider);
//	m_button.addComponent(new RenderComponent("Assets\\Button.png", 30, 30, 30, 30, p_renderer), Types::Render);
//
//	//Button 2
//	m_button2.addComponent(new ButtonComponent(false, 2, 1), Types::Button);
//	m_button2.addComponent(new PositionComponent(150, 650), Types::Position);
//	m_button2.addComponent(new CollisionComponent(m_button2, 30, 30), Types::Collider);
//	m_button2.addComponent(new RenderComponent("Assets\\Button.png", 30, 30, 30, 30, p_renderer), Types::Render);
//	
//	/* //door button
//	m_doorButton.addComponent(new ButtonComponent(false, 1, 2), Types::Button);
//	m_doorButton.addComponent(new PositionComponent(100, 650), Types::Position);
//	m_doorButton.addComponent(new CollisionComponent(m_doorButton, 30, 30), Types::Collider);
//	m_doorButton.addComponent(new RenderComponent("Assets\\DoorButton.png", 30, 30, p_renderer), Types::Render);
//*/
//
//	//Trap 1
//	m_spike.addComponent(new TrapComponent(false, 1), Types::Traps);
//	m_spike.addComponent(new PositionComponent(600, 600), Types::Position);
//	m_spike.addComponent(new CollisionComponent(m_spike, RAT_H, RAT_H, 3), Types::Collider);
//	m_spike.addComponent(new RenderComponent("Assets\\Spike.png", 30, 30, 30, 30, p_renderer), Types::Render);
//
//	//Trap 2
//	m_spike2.addComponent(new TrapComponent(true, 0), Types::Traps);
//	m_spike2.addComponent(new PositionComponent(700, 100), Types::Position);
//	m_spike2.addComponent(new CollisionComponent(m_spike2, RAT_H, RAT_H, 3), Types::Collider);
//	m_spike2.addComponent(new RenderComponent("Assets\\Spike.png", 30, 30, 30, 30, p_renderer), Types::Render);
//
//	//Trap 3
//	m_spike3.addComponent(new TrapComponent(false, 2), Types::Traps);
//	m_spike3.addComponent(new PositionComponent(800, 100), Types::Position);
//	m_spike3.addComponent(new CollisionComponent(m_spike3, RAT_H, RAT_H, 3), Types::Collider);
//	m_spike3.addComponent(new RenderComponent("Assets\\Spike.png", 30, 30, 30, 30, p_renderer), Types::Render);
//
//
//	//door 1
//	/*m_door1.addComponent(new DoorComponent(1),Types::Door);
//	m_door1.addComponent(new PositionComponent(800, 300), Types::Position);
//	m_door1.addComponent(new CollisionComponent(m_door1, 200, 20), Types::Collider);
//	m_door1.addComponent(new RenderComponent("Assets\\Door.png", 200, 20, p_renderer), Types::Render); */
//
//	// cheeses
//	m_goalCheeses.reserve(15);
//	for (int i = 0; i < 15; ++i)
//	{
//		m_goalCheeses.emplace_back();
//		m_goalCheeses.at(i).addComponent(new GoalComponent(), Types::Goal);
//		m_goalCheeses.at(i).addComponent(new PositionComponent(30 + rand() % 1830, 30 + rand() % 1050), Types::Position);
//		m_goalCheeses.at(i).addComponent(new CollisionComponent(m_goalCheeses.at(i), 30, 30), Types::Collider);
//		m_goalCheeses.at(i).addComponent(new RenderComponent("Assets\\cheese.png", 30, 30, 30, 30, p_renderer), Types::Render);
//		m_collisionSystem.addEntity(m_goalCheeses.at(i));
//		m_renderSystem.addEntity(m_goalCheeses.at(i));
//		m_buttonSystem.addEntity(m_goalCheeses.at(i));
//		//m_goalCheese.addComponent(new GoalComponent(), Types::Goal);
//		//m_goalCheese.addComponent(new CollisionComponent(), Types::Collider);
//		//m_goalCheese.addComponent(new PositionComponent(30+rand()%1830, 30+rand()%1050), Types::Position);
//		//m_goalCheese.addComponent(new RenderComponent("Assets\\cheese.png", 30, 30, p_renderer), Types::Render);
//		//m_collisionSystem.addEntity(m_goalCheese);
//		//m_renderSystem.addEntity(m_goalCheese);
//		//m_trapSystem.addEntity(m_goalCheese);
//	}
//
//	//bomb
//	m_bomb.reserve(5);
//	for (int i = 0; i < 5; i++) {
//		m_bomb.emplace_back();
//		m_bomb.at(i).addComponent(new BombComponent(), Types::Bomb);
//		m_bomb.at(i).addComponent(new RenderComponent("Assets\\bomb.png", 30, 30, 300, 300, p_renderer), Types::Render);
//	}
//	m_bomb.at(0).addComponent(new PositionComponent(700, 200), Types::Position);
//	m_bomb.at(0).addComponent(new CollisionComponent(m_bomb.at(0), 30.0f, 30, 30), Types::Collider);
//
//	m_bomb.at(1).addComponent(new PositionComponent(1100, 400), Types::Position);
//	m_bomb.at(1).addComponent(new CollisionComponent(m_bomb.at(1), 30.0f, 30, 30), Types::Collider);
//
//	m_bomb.at(2).addComponent(new PositionComponent(600, 800), Types::Position);
//	m_bomb.at(2).addComponent(new CollisionComponent(m_bomb.at(2), 30.0f, 30, 30), Types::Collider);
//
//	m_bomb.at(3).addComponent(new PositionComponent(500, 700), Types::Position);
//	m_bomb.at(3).addComponent(new CollisionComponent(m_bomb.at(3), 30.0f, 30, 30), Types::Collider);
//
//	m_bomb.at(4).addComponent(new PositionComponent(1050, 600), Types::Position);
//	m_bomb.at(4).addComponent(new CollisionComponent(m_bomb.at(4), 30.0f, 30, 30), Types::Collider);
//
//	for (int i = 0; i < 5; i++) {
//		m_collisionSystem.addEntity(m_bomb.at(i));
//		m_renderSystem.addEntity(m_bomb.at(i));
//		m_bombSystem.addEntity(m_bomb.at(i));
//	}
//
//	//game manager and ui detail
//	m_gameManager.addComponent(new GameComponent(), Types::Game);
//	m_gameManager.addComponent(new PositionComponent((float)SCR_W/2, (float)SCR_H/2), Types::Position);
//	m_gameManager.addComponent(new RenderComponent("Assets\\cheese.png", 30, 30, 30, 30, p_renderer), Types::Render);
//	// Systems
//	//HEALTH All entities
//	m_healthSystem.addEntity(m_rat1);
//	m_healthSystem.addEntity(m_rat4);
//	m_healthSystem.addEntity(m_rat2);
//	m_healthSystem.addEntity(m_rat3);
//
//	//CONTROL Player only
//	m_controlSystem.addEntity(m_rat1);
//	m_controlSystem.addEntity(m_rat4);
//	m_controlSystem.addEntity(m_rat2);
//	m_controlSystem.addEntity(m_rat3);
//
//	//collision System
//	m_collisionSystem.addEntity(m_rat1);
//	m_collisionSystem.addEntity(m_rat4);
//	m_collisionSystem.addEntity(m_rat2);
//	m_collisionSystem.addEntity(m_rat3);
//
//	m_collisionSystem.addEntity(m_button);
//	m_collisionSystem.addEntity(m_button2);
//	//m_collisionSystem.addEntity(m_doorButton);
//
//	m_collisionSystem.addEntity(m_spike);
//	m_collisionSystem.addEntity(m_spike2);
//	m_collisionSystem.addEntity(m_spike3);
//	
//	//m_collisionSystem.addEntity(m_door1);
//
//	//DRAW Draw all of entities
//
//	m_renderSystem.addEntity(m_rat1);
//	m_renderSystem.addEntity(m_rat4);
//	m_renderSystem.addEntity(m_rat2);
//	m_renderSystem.addEntity(m_rat3);
//	
//	/// <summary>
//	/// STATE MACHINE
//	/// </summary>
//	m_stateMachine->setRenderer(p_renderer);
//	m_stateMachine->addEntity(m_rat1);
//	m_stateMachine->addEntity(m_rat4);
//	m_stateMachine->addEntity(m_rat2);
//	m_stateMachine->addEntity(m_rat3);
//	m_stateMachine->setupSprites();
//
//	const auto MAP_PATH = "Assets/map/test.tmx";
//	tiled_map_level = new Level("Test");
//	tiled_map_level->load(MAP_PATH, p_renderer);
//
//	//m_renderSystem.addEntity(m_alien);
//	//m_renderSystem.addEntity(m_dog);
//	//m_renderSystem.addEntity(m_cat);
//
//	m_renderSystem.addEntity(m_button);
//	m_renderSystem.addEntity(m_button2);
//	//m_renderSystem.addEntity(m_doorButton);
//	//m_renderSystem.addEntity(m_door1);
//	m_renderSystem.addEntity(m_spike);
//	m_renderSystem.addEntity(m_spike2);
//	m_renderSystem.addEntity(m_spike3);
//
//
//
//
//
//	//Connect button entity and other entity that require switch	 
//	m_buttonSystem.addEntity(m_button);
//	m_buttonSystem.addEntity(m_button2);
//	//m_buttonSystem.addEntity(m_doorButton);
//
//	m_buttonSystem.addEntity(m_spike);
//	m_buttonSystem.addEntity(m_spike2);
//	m_buttonSystem.addEntity(m_spike3);
//	//m_buttonSystem.addEntity(m_door1);
//
//	// bomb system
//
//	m_bombSystem.addEntity(m_rat1);
//	m_bombSystem.addEntity(m_rat4);
//	m_bombSystem.addEntity(m_rat2);
//	m_bombSystem.addEntity(m_rat3);
//
//	
//	m_gameSystem.addEntity(m_rat1);
//	m_gameSystem.addEntity(m_rat4);
//	m_gameSystem.addEntity(m_rat2);
//	m_gameSystem.addEntity(m_rat3);
//	m_gameSystem.addEntity(m_gameManager);
//	m_gameSystem.setupComponent();
//

	//// TODO: all controllers not connected put AI instead
	//m_aiSystem.addEntity(m_rat3);

	//m_stateMachine = new StateMachineSystem();
	//m_stateMachine->setRenderer(p_renderer);
	//m_stateMachine->addEntity(m_rat1);
	//m_stateMachine->addEntity(m_rat2);
	//m_stateMachine->addEntity(m_rat4);
	//m_stateMachine->setupSprites();
	//m_controlSystem.initStateSystem(m_stateMachine);

	//m_hostGame = new HostingGame();
	m_joinGame = new JoiningGame();
	m_currentState = GameStates::MainMenu;
	m_menuScene = new MenuScene(p_renderer, &m_currentState, controlComp);
	//m_creditsScene = new CreditsScene(p_renderer, &m_currentState);

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
	case GameStates::MainMenu:
		m_menuScene->handleEvents();
		m_currentState = m_menuScene->setNewState();
		m_menuScene->update(dt);
		break;
	case GameStates::Game:
		/*m_healthSystem.update();
		m_aiSystem.update();
		m_buttonSystem.update();
		m_controlSystem.handleInput(dt);
		m_collisionSystem.updateComponent(*tiled_map_level, m_observer);
		m_stateMachine->update();
		m_bombSystem.updateComponent(dt, m_observer);
		m_gameSystem.update(dt);*/
		m_gameScene->update(dt);
		break;
	case GameStates::Hosting:
		m_hostGame->update(dt);
		break;
	case GameStates::Joining:
		m_joinGame->update(dt);
		break;
	case GameStates::Credits:
		//m_creditsScene->update(dt);
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
	case GameStates::MainMenu:
		m_menuScene->render(p_renderer);
		break;
	case GameStates::Game:
		if (m_gameScene == NULL) {
			m_gameScene = new GameScene(p_renderer);
		}
		else {
			/*tiled_map_level->draw(p_renderer);
			m_renderSystem.draw();
			m_gameSystem.draw(m_font);
			m_stateMachine->update();*/
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
		//m_creditsScene->render(p_renderer);
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