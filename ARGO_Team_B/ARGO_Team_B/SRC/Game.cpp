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
	// Dion Debug window
	// p_window = SDL_CreateWindow("ARGO_TEAMB", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 550, 300, SDL_WINDOW_SHOWN);

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

	// Initialise Game Variables

	// Extra info for systems

	/// <summary>
	/// FOR ALL ENTITY
	/// the position component must create before the collision component
	/// </summary>
	// Player
	m_player.addComponent(new PlayerComponent(1), Types::Player); // This must allways be first added
	m_player.addComponent(new HealthComponent(100), Types::Health);
	m_player.addComponent(new PositionComponent(150, 100), Types::Position);
	m_player.addComponent(new CollisionComponent(m_player, 50.0f, RAT_H, RAT_W), Types::Collider);
	m_player.addComponent(new ControlComponent(m_player), Types::Controller);
	m_player.addComponent(new RenderComponent("./Assets/rat.png", RAT_W, RAT_H, p_renderer), Types::Render);
	m_player.addComponent(new AnimatedSpriteComponent("./Assets/SpriteSheet.png", 60, 30, 5, p_renderer), Types::AnimatedSprite);

	// Alien
	m_alien.addComponent(new PlayerComponent(2), Types::Player); // This must allways be first added
	m_alien.addComponent(new HealthComponent(150), Types::Health);
	m_alien.addComponent(new PositionComponent(50, 300), Types::Position);
	m_alien.addComponent(new CollisionComponent(m_alien, RAT_W, RAT_H), Types::Collider);
	m_alien.addComponent(new ControlComponent(m_alien), Types::Controller);
	m_alien.addComponent(new RenderComponent("./Assets/rat2.png", RAT_W, RAT_H, p_renderer), Types::Render);

	// Dog
	m_dog.addComponent(new PlayerComponent(3), Types::Player); // This must allways be first added
	m_dog.addComponent(new HealthComponent(75), Types::Health);
	m_dog.addComponent(new PositionComponent(50, 700), Types::Position);
	m_dog.addComponent(new CollisionComponent(m_dog, RAT_W, RAT_H), Types::Collider);
	m_dog.addComponent(new ControlComponent(m_dog), Types::Controller);
	m_dog.addComponent(new RenderComponent("./Assets/rat3.png", RAT_W, RAT_H, p_renderer), Types::Render);

	// Cat
	m_cat.addComponent(new PlayerComponent(4), Types::Player); // This must allways be first added
	m_cat.addComponent(new HealthComponent(50), Types::Health);
	m_cat.addComponent(new PositionComponent(50, 900), Types::Position);
	m_cat.addComponent(new CollisionComponent(m_cat, RAT_W, RAT_H), Types::Collider);
	m_cat.addComponent(new ControlComponent(m_cat), Types::Controller);
	m_cat.addComponent(new RenderComponent("./Assets/rat4.png", RAT_W, RAT_H, p_renderer), Types::Render);

	/*button test*/
	//Button 1
	m_button.addComponent(new ButtonComponent(false, 1, 1), Types::Button);
	m_button.addComponent(new PositionComponent(600, 50), Types::Position);
	m_button.addComponent(new CollisionComponent(m_button, 30, 30), Types::Collider);
	m_button.addComponent(new RenderComponent("Assets\\Button.png", 30, 30, p_renderer), Types::Render);

	//Button 2
	m_button2.addComponent(new ButtonComponent(false, 2, 1), Types::Button);
	m_button2.addComponent(new PositionComponent(150, 650), Types::Position);
	m_button2.addComponent(new CollisionComponent(m_button2, 30, 30), Types::Collider);
	m_button2.addComponent(new RenderComponent("Assets\\Button.png", 30, 30, p_renderer), Types::Render);
	
	//door button
	/*m_doorButton.addComponent(new ButtonComponent(false, 1, 2), Types::Button);
	m_doorButton.addComponent(new PositionComponent(100, 650), Types::Position);
	m_doorButton.addComponent(new CollisionComponent(m_doorButton, 30, 30), Types::Collider);
	m_doorButton.addComponent(new RenderComponent("Assets\\DoorButton.png", 30, 30, p_renderer), Types::Render);
*/
	//Trap 1
	m_spike.addComponent(new TrapComponent(false, 1), Types::Traps);
	m_spike.addComponent(new PositionComponent(600,600), Types::Position);
	m_spike.addComponent(new CollisionComponent(m_spike, RAT_H, RAT_H, 3), Types::Collider);
	m_spike.addComponent(new RenderComponent("Assets\\Spike.png", 30, 30, p_renderer), Types::Render);

	//Trap 2
	m_spike2.addComponent(new TrapComponent(true, 0), Types::Traps);
	m_spike2.addComponent(new PositionComponent(700, 100), Types::Position);
	m_spike2.addComponent(new CollisionComponent(m_spike2, RAT_H, RAT_H, 3), Types::Collider);
	m_spike2.addComponent(new RenderComponent("Assets\\Spike.png", 30, 30, p_renderer), Types::Render);

	//Trap 3
	m_spike3.addComponent(new TrapComponent(false, 2), Types::Traps);
	m_spike3.addComponent(new PositionComponent(800, 100), Types::Position);
	m_spike3.addComponent(new CollisionComponent(m_spike3, RAT_H, RAT_H, 3), Types::Collider);
	m_spike3.addComponent(new RenderComponent("Assets\\Spike.png", 30, 30, p_renderer), Types::Render);


	//door 1
	/*m_door1.addComponent(new DoorComponent(1),Types::Door);
	m_door1.addComponent(new PositionComponent(800, 300), Types::Position);
	m_door1.addComponent(new CollisionComponent(m_door1, 200, 20), Types::Collider);
	m_door1.addComponent(new RenderComponent("Assets\\Door.png", 200, 20, p_renderer), Types::Render);
*/
	
	//bomb
	m_bomb.addComponent(new BombComponent(), Types::Bomb);
	m_bomb.addComponent(new PositionComponent(700, 200), Types::Position);
	m_bomb.addComponent(new CollisionComponent(m_bomb, 30.0f, 30, 30), Types::Collider);
	m_bomb.addComponent(new RenderComponent("Assets\\bomb.png", 30, 30, p_renderer), Types::Render);

	//game manager and ui detail
	m_gameManager.addComponent(new GameComponent(), Types::Game);
	m_gameManager.addComponent(new PositionComponent((float)SCR_W/2, (float)SCR_H/2), Types::Position);
	m_gameManager.addComponent(new RenderComponent("Assets\\cheese.png", 30, 30, p_renderer), Types::Render);
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

	//collision System
	m_collisionSystem.addEntity(m_player);
	m_collisionSystem.addEntity(m_alien);
	m_collisionSystem.addEntity(m_dog);
	m_collisionSystem.addEntity(m_cat);

	m_collisionSystem.addEntity(m_button);
	m_collisionSystem.addEntity(m_button2);
	//m_collisionSystem.addEntity(m_doorButton);

	m_collisionSystem.addEntity(m_spike);
	m_collisionSystem.addEntity(m_spike2);
	m_collisionSystem.addEntity(m_spike3);
	
	//m_collisionSystem.addEntity(m_door1);

	m_collisionSystem.addEntity(m_bomb);
	//DRAW Draw all of entities
	m_renderSystem.addEntity(m_player);
	m_renderSystem.addEntity(m_alien);
	m_renderSystem.addEntity(m_dog);
	m_renderSystem.addEntity(m_cat);
	

	/// <summary>
	/// STATE MACHINE
	/// </summary>
	m_stateMachine.addEntity(m_player);


	const auto MAP_PATH = "Assets/map/test.tmx";
	tiled_map_level = new Level("Test");
	tiled_map_level->load(MAP_PATH, p_renderer);

	//m_renderSystem.addEntity(m_alien);
	//m_renderSystem.addEntity(m_dog);
	//m_renderSystem.addEntity(m_cat);

	m_renderSystem.addEntity(m_button);
	m_renderSystem.addEntity(m_button2);
	//m_renderSystem.addEntity(m_doorButton);
	//m_renderSystem.addEntity(m_door1);
	m_renderSystem.addEntity(m_spike);
	m_renderSystem.addEntity(m_spike2);
	m_renderSystem.addEntity(m_spike3);


	m_observer = new AudioObserver();
	m_observer->load();
	m_observer->StartBGM(0);

	m_font = new FontObserver(p_renderer);
	m_font->loadFont();

	m_renderSystem.addEntity(m_bomb);

	//Connect button entity and other entity that require switch	 
	m_buttonSystem.addEntity(m_button);
	m_buttonSystem.addEntity(m_button2);
	//m_buttonSystem.addEntity(m_doorButton);

	m_buttonSystem.addEntity(m_spike);
	m_buttonSystem.addEntity(m_spike2);
	m_buttonSystem.addEntity(m_spike3);
	//m_buttonSystem.addEntity(m_door1);

	// bomb system
	m_bombSystem.addEntity(m_bomb);
	m_bombSystem.addEntity(m_player);
	m_bombSystem.addEntity(m_alien);
	m_bombSystem.addEntity(m_dog);
	m_bombSystem.addEntity(m_cat);
	
	// game system
	m_gameSystem.addEntity(m_player);
	m_gameSystem.addEntity(m_alien);
	m_gameSystem.addEntity(m_dog);
	m_gameSystem.addEntity(m_cat);
	m_gameSystem.addEntity(m_gameManager);

	m_gameSystem.setupComponent();
	//cheeses

	//cheeseSpawn(m_collisionSystem, m_renderSystem, m_buttonSystem, *tiled_map_level,p_renderer);
	//m_goalCheeses.reserve(4);
	for (int i = 0; i < tiled_map_level->m_cheese.size(); ++i)
	{
		m_goalCheeses.emplace_back();
		bool canSpawn = false;
		float spawnPointX;
		float spawnPointY;
		//m_goalCheeses.emplace_back();
		//spawnPointX = rand() % 1840+60;
		//spawnPointY = rand() % 1000+60;
		spawnPointX = tiled_map_level->m_cheese[i].x;
		spawnPointY = tiled_map_level->m_cheese[i].y;
		//float centerX = 15;
		//float centerY = 15;
		//float leftE = centerX - 30;
		//float rightE = centerX + 30;
		//float lowE = centerY - 30;
		//float upperE = centerY + 30;
		//canSpawn = canspawnHere(spawnPointX, spawnPointY, leftE, lowE, rightE, upperE);
		m_goalCheeses[i].addComponent(new GoalComponent(), Types::Goal);
		m_goalCheeses[i].addComponent(new PositionComponent(spawnPointX, spawnPointY), Types::Position);
		m_goalCheeses[i].addComponent(new CollisionComponent(m_goalCheeses[i], 30, 30), Types::Collider);
		m_goalCheeses[i].addComponent(new RenderComponent("Assets\\cheese.png", 30, 30, p_renderer), Types::Render);
		m_collisionSystem.addEntity(m_goalCheeses[i]);
		std::cout << "collision system added for " << i << std::endl;
		m_renderSystem.addEntity(m_goalCheeses[i]);
		std::cout << "render system added for " << i << std::endl;
		m_buttonSystem.addEntity(m_goalCheeses[i]);
		std::cout << "button system added for " << i << std::endl;
	}
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

void Game::cheeseSpawn(CollisionSystem t_cs, RenderSystem t_rs, ButtonSystem t_bs, Level& t_cheeses, SDL_Renderer* t_renderer)
{
	m_goalCheeses.reserve(4);
	for (int i = 0; i < t_cheeses.m_cheese.size(); ++i)
	{
		m_goalCheeses.emplace_back();
		bool canSpawn = false;
		float spawnPointX;
		float spawnPointY;
		//m_goalCheeses.emplace_back();
		//spawnPointX = rand() % 1840+60;
		//spawnPointY = rand() % 1000+60;
		spawnPointX = t_cheeses.m_cheese[i].x;
		spawnPointY = t_cheeses.m_cheese[i].y;
		//float centerX = 15;
		//float centerY = 15;
		//float leftE = centerX - 30;
		//float rightE = centerX + 30;
		//float lowE = centerY - 30;
		//float upperE = centerY + 30;
		//canSpawn = canspawnHere(spawnPointX, spawnPointY, leftE, lowE, rightE, upperE);
		m_goalCheeses[i].addComponent(new GoalComponent(), Types::Goal);
		m_goalCheeses[i].addComponent(new PositionComponent(spawnPointX, spawnPointY), Types::Position);
		m_goalCheeses[i].addComponent(new CollisionComponent(m_goalCheeses[i], 30, 30), Types::Collider);
		m_goalCheeses[i].addComponent(new RenderComponent("Assets\\cheese.png", 30, 30, t_renderer), Types::Render);
		t_cs.addEntity(m_goalCheeses[i]);
		std::cout << "collision system added for " << i << std::endl;
		t_rs.addEntity(m_goalCheeses[i]);
		std::cout << "render system added for " << i << std::endl;
		t_bs.addEntity(m_goalCheeses[i]);
		std::cout << "button system added for " << i << std::endl;
	}
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
	m_healthSystem.update();
	m_aiSystem.update();
	m_buttonSystem.update();
	m_controlSystem.handleInput(dt, m_stateMachine,p_renderer);
	m_collisionSystem.updateComponent(*tiled_map_level,m_observer,m_particles,p_renderer);
	m_stateMachine.update();
	m_bombSystem.updateComponent(dt,m_observer);
	m_gameSystem.update(dt);
	for (int i = 0; i < m_particles.size(); i++) {
		// Loops through particle systems
		m_particles.at(i)->update();

		//Checks if the particle system is empty
		if (m_particles.at(i)->m_particles.size() <= 0) {
			// Deletes the particle system
			m_particles.erase(m_particles.begin() + i);
		}
	}
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
	m_gameSystem.draw(m_font);
	// m_stateMachine.update();
	for (ParticleSystem* ps : m_particles) {
		ps->draw(p_renderer); // Draw particle system
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

bool Game::canspawnHere(float spx, float spy, float leftE, float lowE, float rightE, float upperE)
{
	if (spx > leftE && spx<= rightE)
	{
		if (spy>= lowE && spy<= upperE)
		{
			return false;
		}
	}
	return true;
}
