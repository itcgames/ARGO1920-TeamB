#include "GameScene.h"

GameScene::GameScene(SDL_Renderer* t_renderer):
	m_renderer(t_renderer),
	m_restartTimer(6.0f),
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
	const int toReserve = 11 + tiled_map_level->m_cheese.size() + tiled_map_level->m_bomb.size()/*+ tiled_map_level->m_spike.size()*/; // 4 Players + 2 Buttons + 3 Spikes + All cheese and bombs
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
		
		m_collisionSystem.addEntity(*m_entities.at(i));
		m_gameSystem.addEntity(*m_entities.at(i));
		m_bombSystem.addEntity(*m_entities.at(i));
		m_stateMachine->addEntity(*m_entities.at(i));
		
	}
	m_stateMachine->setupSprites();

	/// *** Ensure CHEESE are NEXT entities AFTER PLAYERS at all times ***
	// --Cheese Please
	// We have different cheese sizes on each level, for now let's keep it the same
	// TODO: Instead of capping this consider refactor which adds new cheeses to the factory, having cheese near the end instead so
	// you can easily add the desired ammount of cheese for new levels
	m_cheese_size = tiled_map_level->m_cheese.size();
	for (int i = 0; i < m_cheese_size; ++i)
	{
		float spawnPointX = tiled_map_level->m_cheese[i].x;
		float spawnPointY = tiled_map_level->m_cheese[i].y;
		m_entities.emplace_back(factory->CreateCheese(spawnPointX, spawnPointY));
		m_collisionSystem.addEntity(*m_entities.at(m_entities.size() - 1));
		m_renderSystem.addEntity(*m_entities.at(m_entities.size() - 1));
		m_buttonSystem.addEntity(*m_entities.at(m_entities.size() - 1));
	}

	/// *** Ensure BOMBS are NEXT entities AFTER BOMBS at all times ***
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
	
	for (int i = 0; i <= tiled_map_level->m_spike.size(); i++) {
		float spawnPointX = tiled_map_level->m_spike[i].x;
		float spawnPointY = tiled_map_level->m_spike[i].y;
		m_entities.push_back(factory->CreateTrap(0, true, spawnPointX, spawnPointY));
	}
	m_entities.push_back(factory->CreateTrap(0, true, 700, 100));
	m_entities.push_back(factory->CreateTrap(1, false, 600, 600));
	m_entities.push_back(factory->CreateTrap(2, false, 800, 100));
	m_entities.push_back(factory->CreateTrap(1, false, 1440, 870));
	m_entities.push_back(factory->CreateTrap(2, false, 1440, 810));
		/// Spike Systems
	for (int i = 1; i <= 5 + tiled_map_level->m_spike.size(); i++) {
		m_collisionSystem.addEntity(*m_entities.at(m_entities.size() - i));
		m_renderSystem.addEntity(*m_entities.at(m_entities.size() - i));
		m_buttonSystem.addEntity(*m_entities.at(m_entities.size() - i));
	}

	// Game Manager && UI Detail
	m_entities.push_back(factory->CreateGame()); /// ** Ensure this is the LAST entity at all times
	m_gameSystem.addEntity(*m_entities.at(m_entities.size() - 1));
	m_gameSystem.setupComponent();

	// Creepy Vouyers
	m_observer = new AudioObserver();
	m_observer->load();
	m_observer->StartBGM(1);

	//Adding AI 

	

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

	for (int i = 0; i < 4; i++)
	{
	int num = SDL_NumJoysticks() - 1;
		if(i <= num)
		{
			m_entities.at(i)->addComponent(new ControlComponent(*m_entities.at(i)), Types::Control);
			m_controlSystem.addEntity(*m_entities.at(i));
		}
		else
		{
			m_entities.at(i)->addComponent(new ControlComponent(*m_entities.at(i)), Types::Control);
			m_controlSystem.addEntity(*m_entities.at(i));
			m_entities.at(i)->addComponent(new TestBotBehaviourComponent(m_entities, *m_entities[i], *tiled_map_level), Types::TestBot);
			m_aiSystem.addEntity(*m_entities.at(i));
		}
	}
	m_gameState = dynamic_cast<GameComponent*>(m_entities.at(m_entities.size() - 1)->getComponent(Types::Game));
}

GameScene::GameScene(SDL_Renderer* t_renderer, int playerId) :
	m_renderer(t_renderer),
	m_restartTimer(6.0f),
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
		if (i + 1 != playerId) {
			m_entities.push_back(factory->CreateOnlinePlayer(i + 1, tiled_map_level));
		}
		else {
			m_entities.push_back(factory->CreateOnlineControlPlayer( playerId, tiled_map_level));
			m_controlSystem.addEntity(*m_entities.at(i));
		}

		// TODO: if controller not connect:
		//m_entities.at(i).addComponent(new TestBotBehaviourComponent(m_entities.at(i)), Types::TestBot);

		// Systems
		m_healthSystem.addEntity(*m_entities.at(i));

		m_collisionSystem.addEntity(*m_entities.at(i));
		m_gameSystem.addEntity(*m_entities.at(i));
		m_bombSystem.addEntity(*m_entities.at(i));
		m_stateMachine->addEntity(*m_entities.at(i));
	}
	m_stateMachine->setupSprites();

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
		m_gameSystem.update(dt,m_observer);

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
			resetGame(m_renderer);
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

void GameScene::resetGame(SDL_Renderer* t_renderer) {
	string map;
	m_gameCount++;
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
		return; // exit function
	case -1:  
		// may be redundant case due to other checks but to be safe, TODO: check with controller after remove
		m_gameState->resetGame();
		return; // exit function
	default:
		/*map = "Assets/map/test.tmx";*/
		break;
	}
	m_gameState->resetRound();
	//delete tiled_map_level;
	tiled_map_level = new Level("Level " + m_gameCount);
	tiled_map_level->load(map, m_renderer);
	for (int i = 0; i < 4; i++) {
		PlayerComponent* player = dynamic_cast<PlayerComponent*>(m_entities.at(i)->getComponent(Types::Player));
		player->reset();
		PositionComponent* pos = dynamic_cast<PositionComponent*>(m_entities.at(i)->getComponent(Types::Position));
		pos->reset(tiled_map_level->m_player[i].x, tiled_map_level->m_player[i].y);
		// Ensure Collision resets After Position
		CollisionComponent* col = dynamic_cast<CollisionComponent*>(m_entities.at(i)->getComponent(Types::Collider));
		col->reset();
	}
	
	int num = SDL_NumJoysticks() - 1;
	
	for (int i = 0; i < 4; i++)
	{
		if (i > num)
		{
			TestBotBehaviourComponent* aicomp = dynamic_cast<TestBotBehaviourComponent*>(m_entities[i]->getComponent(Types::TestBot));
			aicomp->setLevel(*tiled_map_level, m_entities);
		}
	}

	// Cheese Please, 
	for (int i = 0; i < m_cheese_size; ++i) // pre increment 
	{
		int index = i + 4; // Start at 4 ( 1 after last player, end at size + 4)
		float spawnPointX = tiled_map_level->m_cheese[i].x;
		float spawnPointY = tiled_map_level->m_cheese[i].y;
		PositionComponent* pos = dynamic_cast<PositionComponent*>(m_entities.at(index)->getComponent(Types::Position));
		pos->reset(spawnPointX, spawnPointY);
		CollisionComponent* col = dynamic_cast<CollisionComponent*>(m_entities.at(index)->getComponent(Types::Collider));
		col->reset();
		GoalComponent* goal = dynamic_cast<GoalComponent*>(m_entities.at(index)->getComponent(Types::Goal));
		goal->reset();

	}

	// Ba-Bomb!
	// TODO: if this breaks make bomb ammount same for all levels like in cheese above
	for (int i = 0; i < tiled_map_level->m_bomb.size(); ++i) // pre increment 
	{
		int index = tiled_map_level->m_cheese.size() + 4; // Start at cheese end plus four, (cheese and bomb have been ordered in factory!)
		float spawnPointX = tiled_map_level->m_bomb[i].x;
		float spawnPointY = tiled_map_level->m_bomb[i].y;
		PositionComponent* pos = dynamic_cast<PositionComponent*>(m_entities.at(index)->getComponent(Types::Position));
		pos->reset(spawnPointX, spawnPointY);
		CollisionComponent* col = dynamic_cast<CollisionComponent*>(m_entities.at(index)->getComponent(Types::Collider));
		col->reset();
		BombComponent* bomb = dynamic_cast<BombComponent*>(m_entities.at(index)->getComponent(Types::Bomb));
		bomb->reset();
	}

	//***  TODO: When changing the AI for non controllers instea of for index 3 do for those out of the first 4 indexes instead!! ***
	//TestBotBehaviourComponent* bot = dynamic_cast<TestBotBehaviourComponent*>(m_entities.at(3)->getComponent(Types::TestBot));
	//bot->reset(*tiled_map_level, m_entities);

	m_restartTimer = 6.0f;
}

string GameScene::playerInfo(int id)
{
	PlayerComponent* m_playerComp = m_playerComp = dynamic_cast<PlayerComponent*>(m_entities[id - 1]->getComponent(Types::Player));;
	PositionComponent* m_playerPos = m_playerPos = dynamic_cast<PositionComponent*>(m_entities[id - 1]->getComponent(Types::Position));;

	//bool playerGetCheese = m_playerComp->getACheese();
	bool playerInteract = m_playerComp->getInteract();
	string transferData = "player : " + to_string(id);
	transferData += "positionX: " + to_string((int)m_playerPos->getPositionX()) + " positionY: " + to_string((int)m_playerPos->getPositionY());
	//transferData += " getCheese: " + to_string(playerGetCheese);
	transferData += " angle: " + to_string((int)m_playerPos->getangle());
	transferData += " interact: " + to_string((int)playerInteract);

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

/// <summary>
/// 0 is the player id
/// 1 is player position x
/// 2 is player position y
/// 3 is player angle
/// 4 is player interact
/// </summary>
/// <param name="player"></param>
void GameScene::setDataToPlayer(vector<int> player)
{
	int id = player[0] - 1;
	PlayerComponent* m_playerComp = dynamic_cast<PlayerComponent*>(m_entities[id]->getComponent(Types::Player));
	PositionComponent* m_playerPos = dynamic_cast<PositionComponent*>(m_entities[id]->getComponent(Types::Position));
	CollisionComponent* m_playerCollider = dynamic_cast<CollisionComponent*>(m_entities[id]->getComponent(Types::Collider));
	AnimatedSpriteComponent* anim = dynamic_cast<AnimatedSpriteComponent*>(m_entities[id]->getComponent(Types::AnimatedSprite));

	m_playerPos->setPosition(player[1],player[2]);
	m_playerCollider->updateCollider(*m_entities[id], player[3]);
	m_playerPos->setangle(player[3]);
	m_playerComp->setInteract(player[4]);
	if (anim->getPrevious()->m_type != States::Walking)
	{
		anim->setCurrent(new WalkingState);
	}
}
