#include "GameScene.h"

GameScene::GameScene(SDL_Renderer* t_renderer):
	m_renderer(t_renderer)
{
	// Extra info for systems
	const auto MAP_PATH = "Assets/map/test.tmx";
	tiled_map_level = new Level("Test");
	tiled_map_level->load(MAP_PATH, t_renderer);
	/// <summary>
	/// STATE MACHINE
	/// </summary>
	m_stateMachine = new StateMachineSystem();
	m_stateMachine->setRenderer(t_renderer);
	/// <summary>
	/// FOR ALL ENTITY
	/// the position component must create before the collision component
	/// Abstract Factory Pattern:
	/// </summary>

	m_entities.reserve(6);
	Factory* factory = new EntityFactory;
	for (int i = 0; i < 4; i++) {
		m_entities.push_back(factory->CreatePlayer(i + 1, tiled_map_level));
				
		// TODO: if controller not connect:
		//m_entities.at(i).addComponent(new TestBotBehaviourComponent(m_entities.at(i)), Types::TestBot);
	
		// Player Systems
		m_healthSystem.addEntity(*m_entities.at(i));
		m_controlSystem.addEntity(*m_entities.at(i));
		m_collisionSystem.addEntity(*m_entities.at(i));
		m_gameSystem.addEntity(*m_entities.at(i));
		m_bombSystem.addEntity(*m_entities.at(i));
		m_stateMachine->addEntity(*m_entities.at(i));
	}
	m_stateMachine->setupSprites();

	float a = 620, b = 175;
	for (int i = 1; i <= 2; i++) {
		float temp = a, a = b, b = temp; // Swap a and b for positions to seperate buttons
		m_entities.push_back(factory->CreateButton(i, a - 10, b + 20)); // manual adjust to get buttons off walls
		// Systems
		m_collisionSystem.addEntity(*m_entities.at(m_entities.size() - 1));
		m_renderSystem.addEntity(*m_entities.at(m_entities.size() - 1));
		m_buttonSystem.addEntity(*m_entities.at(m_entities.size() - 1)); // Connect button entity and other entity that require switch	 
	}


	//Trap 1
	m_spike.addComponent(new TrapComponent(false, 1), Types::Traps);
	m_spike.addComponent(new PositionComponent(600, 600), Types::Position);
	m_spike.addComponent(new CollisionComponent(m_spike, RAT_H, RAT_H, 3), Types::Collider);
	m_spike.addComponent(new RenderComponent("Assets\\Spike.png", 30, 30, 30, 30), Types::Render);

	//Trap 2
	m_spike2.addComponent(new TrapComponent(true, 0), Types::Traps);
	m_spike2.addComponent(new PositionComponent(700, 100), Types::Position);
	m_spike2.addComponent(new CollisionComponent(m_spike2, RAT_H, RAT_H, 3), Types::Collider);
	m_spike2.addComponent(new RenderComponent("Assets\\Spike.png", 30, 30, 30, 30), Types::Render);

	//Trap 3
	m_spike3.addComponent(new TrapComponent(false, 2), Types::Traps);
	m_spike3.addComponent(new PositionComponent(800, 100), Types::Position);
	m_spike3.addComponent(new CollisionComponent(m_spike3, RAT_H, RAT_H, 3), Types::Collider);
	m_spike3.addComponent(new RenderComponent("Assets\\Spike.png", 30, 30, 30, 30), Types::Render);


	//cheeses
	m_goalCheeses.reserve(tiled_map_level->m_cheese.size());
	for (int i = 0; i < tiled_map_level->m_cheese.size(); ++i)
	{
		m_goalCheeses.emplace_back();
		bool canSpawn = false;
		float spawnPointX;
		float spawnPointY;
		spawnPointX = tiled_map_level->m_cheese[i].x;
		spawnPointY = tiled_map_level->m_cheese[i].y;
		m_goalCheeses[i].addComponent(new GoalComponent(), Types::Goal);
		m_goalCheeses[i].addComponent(new PositionComponent(spawnPointX, spawnPointY), Types::Position);
		m_goalCheeses[i].addComponent(new CollisionComponent(m_goalCheeses[i], 30.0f, 30, 30), Types::Collider);
		m_goalCheeses[i].addComponent(new RenderComponent("Assets\\cheese.png", 30, 30, 30, 30), Types::Render);
		m_collisionSystem.addEntity(m_goalCheeses[i]);
		std::cout << "collision system added for " << i << std::endl;
		m_renderSystem.addEntity(m_goalCheeses[i]);
		std::cout << "render system added for " << i << std::endl;
		m_buttonSystem.addEntity(m_goalCheeses[i]);
		std::cout << "button system added for " << i << std::endl;
	}

	//bombs
	m_bombs.reserve(tiled_map_level->m_bomb.size());
	for (int i = 0; i < tiled_map_level->m_bomb.size(); ++i)
	{
		m_bombs.emplace_back();
		float spawnPointX;
		float spawnPointY;
		spawnPointX = tiled_map_level->m_bomb[i].x;
		spawnPointY = tiled_map_level->m_bomb[i].y;
		m_bombs[i].addComponent(new BombComponent(), Types::Bomb);
		m_bombs[i].addComponent(new PositionComponent(spawnPointX, spawnPointY), Types::Position);
		m_bombs[i].addComponent(new CollisionComponent(m_bombs[i], 30.0f, 30, 30), Types::Collider);
		m_bombs[i].addComponent(new RenderComponent("Assets\\bomb.png", 30, 30, 300, 300), Types::Render);
		m_collisionSystem.addEntity(m_bombs[i]);
		std::cout << "collision system added for " << i << std::endl;
		m_renderSystem.addEntity(m_bombs[i]);
		std::cout << "render system added for " << i << std::endl;
		m_bombSystem.addEntity(m_bombs[i]);
		std::cout << "button system added for " << i << std::endl;
	}

	//game manager and ui detail
	m_gameManager.addComponent(new GameComponent(), Types::Game);
	m_gameManager.addComponent(new PositionComponent((float)SCR_W / 2, (float)SCR_H / 2), Types::Position);
	m_gameManager.addComponent(new RenderComponent("Assets\\cheese.png", 30, 30, 30, 30), Types::Render);
	
	// Systems
	m_collisionSystem.addEntity(m_spike);
	m_collisionSystem.addEntity(m_spike2);
	m_collisionSystem.addEntity(m_spike3);

	m_renderSystem.addEntity(m_spike);
	m_renderSystem.addEntity(m_spike2);
	m_renderSystem.addEntity(m_spike3);

	m_observer = new AudioObserver();
	m_observer->load();
	m_observer->StartBGM(0);

	m_font = new FontObserver(t_renderer);
	m_font->loadFont();

	m_buttonSystem.addEntity(m_spike);
	m_buttonSystem.addEntity(m_spike2);
	m_buttonSystem.addEntity(m_spike3);

	m_gameSystem.addEntity(m_gameManager);
	m_gameSystem.setupComponent();

	/// <summary>
	///  CANNOT pass renderer to Factory as it needs const inputs but renderer cannot be, so do like so for now
	/// </summary>
	/// <param name="t_renderer"></param>
	for (Entity* e : m_entities) {
		if (e->getComponent(Types::AnimatedSprite) != NULL) {
			AnimatedSpriteComponent* a = dynamic_cast<AnimatedSpriteComponent*>(e->getComponent(Types::AnimatedSprite));
			if (nullptr != a) {
				a->init(m_renderer);
			}
		}
		else if (e->getComponent(Types::Render) != NULL) {
			RenderComponent* a = dynamic_cast<RenderComponent*>(e->getComponent(Types::Render));
			if (nullptr != a) {
				a->init(m_renderer);
			}
		}	
	}
}

GameScene::~GameScene()
{
}

void GameScene::update(float dt)
{
	m_healthSystem.update();
	m_aiSystem.update();
	m_buttonSystem.update();
	m_controlSystem.handleInput(dt, m_stateMachine, m_renderer, m_particles);
	m_collisionSystem.updateComponent(*tiled_map_level, m_observer, m_particles, m_renderer);
	m_stateMachine->update();
	m_bombSystem.updateComponent(dt, m_observer);
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

void GameScene::render()
{
	tiled_map_level->draw(m_renderer);
	m_renderSystem.draw();
	m_gameSystem.draw(m_font);
	m_stateMachine->update();

	for (ParticleSystem* ps : m_particles) {
		ps->draw(m_renderer); // Draw particle system
	}
}
