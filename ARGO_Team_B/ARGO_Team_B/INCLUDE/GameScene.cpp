#include "GameScene.h"

GameScene::GameScene(SDL_Renderer* t_renderer, GameStates* t_state):
	m_currentState(t_state)
{
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
	m_player.addComponent(new RenderComponent("./Assets/rat.png", RAT_W, RAT_H, t_renderer), Types::Render);
	m_player.addComponent(new AnimatedSpriteComponent("./Assets/SpriteSheet.png", 60, 30, 5, t_renderer), Types::AnimatedSprite);

	// Alien
	m_alien.addComponent(new PlayerComponent(2), Types::Player); // This must allways be first added
	m_alien.addComponent(new HealthComponent(150), Types::Health);
	m_alien.addComponent(new PositionComponent(50, 300), Types::Position);
	m_alien.addComponent(new CollisionComponent(m_alien, RAT_W, RAT_H), Types::Collider);
	m_alien.addComponent(new ControlComponent(m_alien), Types::Controller);
	m_alien.addComponent(new RenderComponent("./Assets/rat2.png", RAT_W, RAT_H, t_renderer), Types::Render);

	// Dog
	m_dog.addComponent(new PlayerComponent(3), Types::Player); // This must allways be first added
	m_dog.addComponent(new HealthComponent(75), Types::Health);
	m_dog.addComponent(new PositionComponent(50, 700), Types::Position);
	m_dog.addComponent(new CollisionComponent(m_dog, RAT_W, RAT_H), Types::Collider);
	m_dog.addComponent(new ControlComponent(m_dog), Types::Controller);
	m_dog.addComponent(new RenderComponent("./Assets/rat3.png", RAT_W, RAT_H, t_renderer), Types::Render);

	// Cat
	m_cat.addComponent(new PlayerComponent(4), Types::Player); // This must allways be first added
	m_cat.addComponent(new HealthComponent(50), Types::Health);
	m_cat.addComponent(new PositionComponent(50, 900), Types::Position);
	m_cat.addComponent(new CollisionComponent(m_cat, RAT_W, RAT_H), Types::Collider);
	m_cat.addComponent(new ControlComponent(m_cat), Types::Controller);
	m_cat.addComponent(new RenderComponent("./Assets/rat4.png", RAT_W, RAT_H, t_renderer), Types::Render);

	/*button test*/
	//Button 1
	m_button.addComponent(new ButtonComponent(false, 1, 1), Types::Button);
	m_button.addComponent(new PositionComponent(600, 50), Types::Position);
	m_button.addComponent(new CollisionComponent(m_button, 30, 30), Types::Collider);
	m_button.addComponent(new RenderComponent("Assets\\Button.png", 30, 30, t_renderer), Types::Render);

	//Button 2
	m_button2.addComponent(new ButtonComponent(false, 2, 1), Types::Button);
	m_button2.addComponent(new PositionComponent(150, 650), Types::Position);
	m_button2.addComponent(new CollisionComponent(m_button2, 30, 30), Types::Collider);
	m_button2.addComponent(new RenderComponent("Assets\\Button.png", 30, 30, t_renderer), Types::Render);

	//door button
	m_doorButton.addComponent(new ButtonComponent(false, 1, 2), Types::Button);
	m_doorButton.addComponent(new PositionComponent(100, 650), Types::Position);
	m_doorButton.addComponent(new CollisionComponent(m_doorButton, 30, 30), Types::Collider);
	m_doorButton.addComponent(new RenderComponent("Assets\\DoorButton.png", 30, 30, t_renderer), Types::Render);

	//Trap 1
	m_spike.addComponent(new TrapComponent(false, 1), Types::Traps);
	m_spike.addComponent(new PositionComponent(600, 600), Types::Position);
	m_spike.addComponent(new CollisionComponent(m_spike, RAT_H, RAT_H, 3), Types::Collider);
	m_spike.addComponent(new RenderComponent("Assets\\Spike.png", 30, 30, t_renderer), Types::Render);

	//Trap 2
	m_spike2.addComponent(new TrapComponent(true, 0), Types::Traps);
	m_spike2.addComponent(new PositionComponent(700, 100), Types::Position);
	m_spike2.addComponent(new CollisionComponent(m_spike2, RAT_H, RAT_H, 3), Types::Collider);
	m_spike2.addComponent(new RenderComponent("Assets\\Spike.png", 30, 30, t_renderer), Types::Render);

	//Trap 3
	m_spike3.addComponent(new TrapComponent(false, 2), Types::Traps);
	m_spike3.addComponent(new PositionComponent(800, 100), Types::Position);
	m_spike3.addComponent(new CollisionComponent(m_spike3, RAT_H, RAT_H, 3), Types::Collider);
	m_spike3.addComponent(new RenderComponent("Assets\\Spike.png", 30, 30, t_renderer), Types::Render);


	//door 1
	m_door1.addComponent(new DoorComponent(1), Types::Door);
	m_door1.addComponent(new PositionComponent(800, 300), Types::Position);
	m_door1.addComponent(new CollisionComponent(m_door1, 200, 20), Types::Collider);
	m_door1.addComponent(new RenderComponent("Assets\\Door.png", 200, 20, t_renderer), Types::Render);

	// cheeses
	m_goalCheeses.reserve(15);
	for (int i = 0; i < 15; ++i)
	{
		m_goalCheeses.emplace_back();
		m_goalCheeses.at(i).addComponent(new GoalComponent(), Types::Goal);
		m_goalCheeses.at(i).addComponent(new PositionComponent(30 + rand() % 1830, 30 + rand() % 1050), Types::Position);
		m_goalCheeses.at(i).addComponent(new CollisionComponent(m_goalCheeses.at(i), 30, 30), Types::Collider);
		m_goalCheeses.at(i).addComponent(new RenderComponent("Assets\\cheese.png", 30, 30, t_renderer), Types::Render);
		m_collisionSystem.addEntity(m_goalCheeses.at(i));
		m_renderSystem.addEntity(m_goalCheeses.at(i));
		m_buttonSystem.addEntity(m_goalCheeses.at(i));
		//m_goalCheese.addComponent(new GoalComponent(), Types::Goal);
		//m_goalCheese.addComponent(new CollisionComponent(), Types::Collider);
		//m_goalCheese.addComponent(new PositionComponent(30+rand()%1830, 30+rand()%1050), Types::Position);
		//m_goalCheese.addComponent(new RenderComponent("Assets\\cheese.png", 30, 30, p_renderer), Types::Render);
		//m_collisionSystem.addEntity(m_goalCheese);
		//m_renderSystem.addEntity(m_goalCheese);
		//m_trapSystem.addEntity(m_goalCheese);
	}

	//bomb
	m_bomb.addComponent(new BombComponent(), Types::Bomb);
	m_bomb.addComponent(new PositionComponent(700, 200), Types::Position);
	m_bomb.addComponent(new CollisionComponent(m_bomb, 30.0f, 30, 30), Types::Collider);
	m_bomb.addComponent(new RenderComponent("Assets\\bomb.png", 30, 30, t_renderer), Types::Render);

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
	m_collisionSystem.addEntity(m_doorButton);

	m_collisionSystem.addEntity(m_spike);
	m_collisionSystem.addEntity(m_spike2);
	m_collisionSystem.addEntity(m_spike3);

	m_collisionSystem.addEntity(m_door1);

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
	tiled_map_level->load(MAP_PATH, t_renderer);

	//m_renderSystem.addEntity(m_alien);
	//m_renderSystem.addEntity(m_dog);
	//m_renderSystem.addEntity(m_cat);

	m_renderSystem.addEntity(m_button);
	m_renderSystem.addEntity(m_button2);
	m_renderSystem.addEntity(m_doorButton);
	m_renderSystem.addEntity(m_door1);
	m_renderSystem.addEntity(m_spike);
	m_renderSystem.addEntity(m_spike2);
	m_renderSystem.addEntity(m_spike3);
	m_observer = new AudioObserver();
	m_observer->load();
	m_observer->StartBGM(1);



	m_renderSystem.addEntity(m_bomb);

	//Connect button entity and other entity that require switch	 
	m_buttonSystem.addEntity(m_button);
	m_buttonSystem.addEntity(m_button2);
	m_buttonSystem.addEntity(m_doorButton);

	m_buttonSystem.addEntity(m_spike);
	m_buttonSystem.addEntity(m_spike2);
	m_buttonSystem.addEntity(m_spike3);
	m_buttonSystem.addEntity(m_door1);

	// bomb system
	m_bombSystem.addEntity(m_bomb);
	m_bombSystem.addEntity(m_player);
	m_bombSystem.addEntity(m_alien);
	m_bombSystem.addEntity(m_dog);
	m_bombSystem.addEntity(m_cat);
}

GameScene::~GameScene()
{
}

void GameScene::update(float dt)
{
	m_healthSystem.update();
	m_aiSystem.update();
	m_buttonSystem.update();
	m_controlSystem.handleInput(dt, m_stateMachine);
	m_collisionSystem.updateComponent(*tiled_map_level, m_observer);
	m_stateMachine.update();
	m_bombSystem.updateComponent(dt, m_observer);
}

void GameScene::render(SDL_Renderer * t_renderer)
{
	tiled_map_level->draw(t_renderer);
	m_renderSystem.draw();
}
