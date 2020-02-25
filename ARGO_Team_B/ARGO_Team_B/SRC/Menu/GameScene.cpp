#include "GameScene.h"

GameScene::GameScene(SDL_Renderer* t_renderer):
	m_renderer(t_renderer)
{
	// Extra info for systems
	const auto MAP_PATH = "Assets/map/test.tmx";
	tiled_map_level = new Level("Test");
	tiled_map_level->load(MAP_PATH, t_renderer);

	/// STATE MACHINE
	m_stateMachine = new StateMachineSystem();
	m_stateMachine->setRenderer(t_renderer);

	/// Abstract Factory Pattern:
	m_entities.reserve(9 + tiled_map_level->m_cheese.size()); // increasing each addition to Factory
	Factory* factory = new EntityFactory;

	/// Players
	for (int i = 0; i < 4; i++) {
		m_entities.push_back(factory->CreatePlayer(i + 1, tiled_map_level));
				
		// TODO: if controller not connect:
		//m_entities.at(i).addComponent(new TestBotBehaviourComponent(m_entities.at(i)), Types::TestBot);
	
		// Systems
		m_healthSystem.addEntity(*m_entities.at(i));
		m_controlSystem.addEntity(*m_entities.at(i));
		m_collisionSystem.addEntity(*m_entities.at(i));
		m_gameSystem.addEntity(*m_entities.at(i));
		m_bombSystem.addEntity(*m_entities.at(i));
		m_stateMachine->addEntity(*m_entities.at(i));
	}
	m_stateMachine->setupSprites();

	/// Buttons
	float a = 620.0f;
	float b = 175;
	for (int i = 1; i <= 2; i++) {
		float temp = a;
		a = b;
		b = temp; // Swap a and b for positions to seperate buttons
		m_entities.push_back(factory->CreateButton(i, a - 10, b + 20)); // manual adjust to get buttons off walls
		// Systems
		m_collisionSystem.addEntity(*m_entities.at(m_entities.size() - 1));
		m_renderSystem.addEntity(*m_entities.at(m_entities.size() - 1));
		m_buttonSystem.addEntity(*m_entities.at(m_entities.size() - 1)); // Connect button entity and other entity that require switch	 
	}

	/// Spikes
	m_entities.push_back(factory->CreateTrap(1, false, 600, 600));
	m_entities.push_back(factory->CreateTrap(0, true, 700, 100));
	m_entities.push_back(factory->CreateTrap(2, false, 800, 100));
		/// Spike Systems
	for (int i = 1; i <= 3; i++) {
		m_collisionSystem.addEntity(*m_entities.at(m_entities.size() - i));
		m_renderSystem.addEntity(*m_entities.at(m_entities.size() - i));
		m_buttonSystem.addEntity(*m_entities.at(m_entities.size() - i));
	}

	// Cheese Please
	for (int i = 0; i < tiled_map_level->m_cheese.size(); ++i)
	{
		float spawnPointX = tiled_map_level->m_cheese[i].x;
		float spawnPointY = tiled_map_level->m_cheese[i].y;
		//m_entities.;
		m_entities.emplace_back(factory->CreateCheese(spawnPointX, spawnPointY));
		m_collisionSystem.addEntity(*m_entities.at(m_entities.size() - 1));
		m_renderSystem.addEntity(*m_entities.at(m_entities.size() - 1));
		m_buttonSystem.addEntity(*m_entities.at(m_entities.size() - 1));
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
	

	m_observer = new AudioObserver();
	m_observer->load();
	m_observer->StartBGM(0);

	m_font = new FontObserver(t_renderer);
	m_font->loadFont();


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
