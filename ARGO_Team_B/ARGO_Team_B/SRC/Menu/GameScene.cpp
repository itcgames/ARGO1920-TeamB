#include "GameScene.h"

GameScene::GameScene(SDL_Renderer* t_renderer):
	m_renderer(t_renderer),
	m_isEndScreenDone{false},
	m_gameCount(1)
{
	m_view.h = SCR_H;
	m_view.w = SCR_W;
	m_view.x = 0;
	m_view.y = 0;

	SDL_RenderSetViewport(m_renderer, &m_view);

	// Extra info for systems
	const auto MAP_PATH = "Assets/map/test.tmx";
	tiled_map_level = new Level("Test");
	tiled_map_level->load(MAP_PATH, t_renderer);

	/// STATE MACHINE
	m_stateMachine = new StateMachineSystem();
	m_stateMachine->setRenderer(t_renderer);

	/// Abstract Factory Pattern:
	const int toReserve = 9 + tiled_map_level->m_cheese.size() + tiled_map_level->m_bomb.size(); // 4 Players + 2 Buttons + 3 Spikes + All cheese and bombs
	m_entities.reserve(toReserve); // increase with each addition to Factory (see above)
	Factory* factory = new EntityFactory;

	/// *** Ensure Players are FIRST four entities in list at all times
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
		m_entities.emplace_back(factory->CreateCheese(spawnPointX, spawnPointY));
		m_collisionSystem.addEntity(*m_entities.at(m_entities.size() - 1));
		m_renderSystem.addEntity(*m_entities.at(m_entities.size() - 1));
		m_buttonSystem.addEntity(*m_entities.at(m_entities.size() - 1));
	}

	// Ba-Bomb!
	for (int i = 0; i < tiled_map_level->m_bomb.size(); ++i)
	{
		float spawnPointX = tiled_map_level->m_bomb[i].x;
		float spawnPointY = tiled_map_level->m_bomb[i].y;
		m_entities.emplace_back(factory->CreateBomb(spawnPointX, spawnPointY));
		m_collisionSystem.addEntity(*m_entities.at(m_entities.size() - 1));
		m_renderSystem.addEntity(*m_entities.at(m_entities.size() - 1));
		m_bombSystem.addEntity(*m_entities.at(m_entities.size() - 1));
	}

	// Game Manager && UI Detail
	m_entities.push_back(factory->CreateGame()); /// ** Ensure this is the LAST entity at all times
	m_gameSystem.addEntity(*m_entities.at(m_entities.size() - 1));
	m_gameSystem.setupComponent();

	// Creepy Vouyers
	m_observer = new AudioObserver();
	m_observer->load();
	//m_observer->StartBGM(1);


	m_font = new FontObserver(t_renderer);
	m_font->loadFont();

	/// <summary>
	/// CANNOT pass renderer to Factory as it needs const inputs and renderer cannot be, so do like so for now
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
	m_gameState = dynamic_cast<GameComponent*>(m_entities.at(m_entities.size() - 1)->getComponent(Types::Game));
}

GameScene::~GameScene()
{
}

void GameScene::update(float dt)
{
	GameComponent* m_game = dynamic_cast<GameComponent*>(m_entities.at(m_entities.size() - 1)->getComponent(Types::Game));
	if (!m_game->getGameover()) {
		m_healthSystem.update();
		m_aiSystem.update();
		m_buttonSystem.update();
		m_controlSystem.handleInput(dt, m_stateMachine, m_renderer, m_particles);
		m_collisionSystem.updateComponent(*tiled_map_level, m_observer, m_particles, m_renderer, m_view);
		//m_stateMachine->update();
		m_bombSystem.updateComponent(dt, m_observer, m_view);
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
	else {
		m_restartTimer -= dt;
		if (m_restartTimer <= 0) {
			// let end screen show
			if (!m_isEndScreenDone)
			{
				m_restartTimer += 2.5f;
				m_isEndScreenDone = true;
			}
			else {
				resetGame();
			}
			// restart code here
		}
	}
}

void GameScene::render()
{
	tiled_map_level->draw(m_renderer);
	m_renderSystem.draw();
	m_gameSystem.draw(m_font, m_restartTimer);
	m_stateMachine->update();

	for (ParticleSystem* ps : m_particles) {
		ps->draw(m_renderer); // Draw particle system
	}

	SDL_RenderSetViewport(m_renderer, &m_view);

}

void GameScene::resetGame() {
	string map;
	m_gameCount++;
	m_isEndScreenDone = false;
	if (m_gameState->getGameCount() != -1) // game over early code
	{
		m_gameState->setGameCount(m_gameCount);
	}
	else {
		m_gameCount = -1;
	}
	switch (m_gameCount) {
	case 2:
		map = "Assets/map/test2.tmx";
		break;
	case 3:
		map = "Assets/map/test3.tmx";
		break;
	case 4:
		map = "Assets/map/test4.tmx";
		break;
	case 5:
		map = "Assets/map/test5.tmx";
		break;
	case 6:
		m_gameState->resetGame();
		break;
	default:
		break;
	}
	m_gameState->resetRound();
	tiled_map_level->load(map, m_renderer);
	for (int i = 0; i < 4; i++) {
		PlayerComponent* player = dynamic_cast<PlayerComponent*>(m_entities.at(i)->getComponent(Types::Player));
		player->reset();
		PositionComponent* pos = dynamic_cast<PositionComponent*>(m_entities.at(i)->getComponent(Types::Position));
		pos->reset(i + 1, tiled_map_level);
	}
}

SDL_Point GameScene::playerPosition(int id) {

	PositionComponent* m_player = NULL;
	switch (id)
	{
	case 1:
		m_player = dynamic_cast<PositionComponent*>(m_entities[0]->getComponent(Types::Player));
		break;
	case 2:
		m_player = dynamic_cast<PositionComponent*>(m_entities[0]->getComponent(Types::Player));
		break;
	case 3:
		m_player = dynamic_cast<PositionComponent*>(m_entities[0]->getComponent(Types::Player));
		break;
	case 4:
		m_player = dynamic_cast<PositionComponent*>(m_entities[0]->getComponent(Types::Player));
		break;
	default:
		break;
	}
	SDL_Point positionData = { m_player->getPositionX(), m_player->getPositionY() };
	return positionData;
}

bool GameScene::playerGetCheese(int id) {

	PlayerComponent* m_player = NULL;

	switch (id)
	{
	case 1:
		m_player = dynamic_cast<PlayerComponent*>(m_entities[0]->getComponent(Types::Player));
		break;
	case 2:
		m_player = dynamic_cast<PlayerComponent*>(m_entities[0]->getComponent(Types::Player));
		break;
	case 3:
		m_player = dynamic_cast<PlayerComponent*>(m_entities[0]->getComponent(Types::Player));
		break;
	case 4:
		m_player = dynamic_cast<PlayerComponent*>(m_entities[0]->getComponent(Types::Player));
		break;
	default:
		break;
	}

	bool playerGetCheese = m_player->getACheese();

	return playerGetCheese;
}

string GameScene::playerInfo(int id)
{
	PlayerComponent* m_playerComp = NULL;
	PositionComponent* m_playerPos = NULL;

	switch (id)
	{
	case 1:
		m_playerComp = dynamic_cast<PlayerComponent*>(m_entities[0]->getComponent(Types::Player));
		m_playerPos = dynamic_cast<PositionComponent*>(m_entities[0]->getComponent(Types::Player));
		break;
	case 2:
		m_playerComp = dynamic_cast<PlayerComponent*>(m_entities[0]->getComponent(Types::Player));
		m_playerPos = dynamic_cast<PositionComponent*>(m_entities[0]->getComponent(Types::Player));
		break;
	case 3:
		m_playerComp = dynamic_cast<PlayerComponent*>(m_entities[0]->getComponent(Types::Player));
		m_playerPos = dynamic_cast<PositionComponent*>(m_entities[0]->getComponent(Types::Player));
		break;
	case 4:
		m_playerComp = dynamic_cast<PlayerComponent*>(m_entities[0]->getComponent(Types::Player));
		m_playerPos = dynamic_cast<PositionComponent*>(m_entities[0]->getComponent(Types::Player));
		break;
	default:
		break;
	}

	bool playerGetCheese = m_playerComp->getACheese();
	bool playerInteract = m_playerComp->getInteract();

	string transferData = "positionX: " + to_string(m_playerPos->getPositionX()) + "positionY: " + to_string(m_playerPos->getPositionY());
	transferData += " getCheese: " + to_string(playerGetCheese);
	transferData += " interact: " + to_string(playerInteract);

	return transferData;
}

float GameScene::gameStartCountdown() {
	GameComponent* m_gameState = dynamic_cast<GameComponent*>(m_entities.at(m_entities.size() - 1)->getComponent(Types::Game));
	return m_gameState->getstartCountdown();
}

float GameScene::ingameTimer() {
	GameComponent* m_gameState = dynamic_cast<GameComponent*>(m_entities.at(m_entities.size() - 1)->getComponent(Types::Game));
	return m_gameState->getGameTimer();
}