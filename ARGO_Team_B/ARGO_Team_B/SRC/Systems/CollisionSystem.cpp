#include "CollisionSystem.h"

CollisionSystem::CollisionSystem()

{
}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::updateComponent(Component* component)
{
}

void CollisionSystem::updateComponent(Level& t_level, AudioObserver* t_observer, std::vector<ParticleSystem*>& t_ps, SDL_Renderer* t_renderer, SDL_Rect & t_shake)
{
	searchEntities();

	vector<CollisionComponent*> playerColliders;

	for (Entity& player : m_playerEntitys) {
		CollisionComponent* playerComp = dynamic_cast<CollisionComponent*>(player.getComponent(Types::Collider));
		PositionComponent* posComp = dynamic_cast<PositionComponent*>(player.getComponent(Types::Position));
		playerColliders.push_back(playerComp);

		m_positionComp = static_cast<PositionComponent*>(player.getComponent(Types::Position));
		x1 = m_positionComp->getPositionX();
		y1 = m_positionComp->getPositionY();
		//tileCollision(playerComp, posComp, t_level, t_observer);
		tileCollision(x1, y1 + (RAT_H / 4), RAT_W, RAT_H / 2, t_level,t_observer);

	}

	for (Entity& bomb : m_bombEntitys) {
		BombComponent* bombComp = static_cast<BombComponent*>(bomb.getComponent(Types::Bomb));
		if (bombComp->getState() != BombState::Removed) {

			CollisionComponent* bombCollider = static_cast<CollisionComponent*>(bomb.getComponent(Types::Collider));

			bombCollider->updateCollider(bomb);

			if (bombComp->getState() == BombState::Explode) {
				TileBombCollision(&t_level, bombCollider);
			}
		}
	}


	// player 1 and player 2 collision check
	if (checkCollision(playerColliders[0]->getAABBCollider(), playerColliders[1]->getAABBCollider())) {

	}

	// player 3 and player 4 collision check
	if (checkCollision(playerColliders[2]->getAABBCollider(), playerColliders[3]->getAABBCollider())) {

	}


	/// <summary>
	/// check collision between player and button
	/// </summary>
	for (Entity& buttonEntity : m_buttonEntitys) {
		ButtonComponent* button = static_cast<ButtonComponent*>(buttonEntity.getComponent(Types::Button));
		// check is button on the map
		if (button->getAlive()) {

			CollisionComponent* buttonCollider = static_cast<CollisionComponent*>(buttonEntity.getComponent(Types::Collider));

			// update the component state **necessaey update**
			buttonCollider->updateCollider(buttonEntity);

			for (Entity& playerEntitys : m_playerEntitys) {
				CollisionComponent* playerCollision = static_cast<CollisionComponent*>(playerEntitys.getComponent(Types::Collider));

					
				
				PlayerComponent* player = static_cast<PlayerComponent*>(playerEntitys.getComponent(Types::Player));
				
				// check for 2 different button, 1 for trap button, 2 for door button
				switch (button->getType())
				{
				case 1:
					if (checkCollision( buttonCollider->getAABBCollider(), playerCollision->getPolyCollider())) {

						button->setState(true);
						t_observer->onNotify(AudioObserver::CLICK);

					}
					break;
				case 2:
					if (checkCollision(buttonCollider->getAABBCollider(), playerCollision->getPolyCollider())) {
						// 1,3 for red team
						if (player->getId() == 1 || player->getId() == 3) {
							button->setRedDoor(true);
						}
						// 2,4 for green team
						if (player->getId() == 2 || player->getId() == 4) {
							button->setGreenDoor(true);
						}
					}
					break;
				default:
					break;
				}

			}
		}
	}

	/// <summary>
	///  check collision between player and traps
	/// </summary>
	for (Entity& trapEntity : m_trapEntitys) {

		TrapComponent* trap = static_cast<TrapComponent*>(trapEntity.getComponent(Types::Traps));

		// check is button on the map
		if (trap->getAlive()) {

			CollisionComponent* trapCollider = static_cast<CollisionComponent*>(trapEntity.getComponent(Types::Collider));

			// update the component state **necessaey update**
			trapCollider->updateCollider(trapEntity);

			for (Entity& playerEntitys : m_playerEntitys) {
				CollisionComponent* player = static_cast<CollisionComponent*>(playerEntitys.getComponent(Types::Collider));

				HealthComponent* playerHealth = static_cast<HealthComponent*>(playerEntitys.getComponent(Types::Health));
				PositionComponent* playerPos = static_cast<PositionComponent*>(playerEntitys.getComponent(Types::Position));
				if (playerHealth->getAlive()) {
					if (checkCollision( trapCollider->getAABBCollider(), player->getPolyCollider()) ) {
						t_observer->onNotify(AudioObserver::CLICK);
						cout << "player die" << endl;
						playerPos->backToStart();
						//playerHealth->dead();
					}
				}
			}
		}
	}
	/// <summary>
	/// check collision between player and door
	///  </summary>
	for (Entity& doorEntity : m_doorEntitys) {
		DoorComponent* door = static_cast<DoorComponent*>(doorEntity.getComponent(Types::Door));

		// if the door not open for two team, check collision
		if (!door->getGreenDoor() || !door->getRedDoor()) {

			CollisionComponent* doorCollider = static_cast<CollisionComponent*>(doorEntity.getComponent(Types::Collider));

			doorCollider->updateCollider(doorEntity);

			// red door open, check with player 1 and 3
			if (!door->getRedDoor()) {
				if (checkCollision( doorCollider->getAABBCollider(), playerColliders[0]->getPolyCollider())) {
					PlayerComponent* player = static_cast<PlayerComponent*>(m_playerEntitys[0].getComponent(Types::Player));
					player->setMoveable(false);
				}

				if (checkCollision(doorCollider->getAABBCollider(), playerColliders[2]->getPolyCollider())) {
					PlayerComponent* player = static_cast<PlayerComponent*>(m_playerEntitys[2].getComponent(Types::Player));
					player->setMoveable(false);
				}
			}

			// green door open, check with player 2 and 4
			if (!door->getGreenDoor()) {
				if (checkCollision( doorCollider->getAABBCollider(), playerColliders[1]->getPolyCollider())) {
					PlayerComponent* player = static_cast<PlayerComponent*>(m_playerEntitys[1].getComponent(Types::Player));
					player->setMoveable(false);
				}

				if (checkCollision(doorCollider->getAABBCollider(), playerColliders[3]->getPolyCollider())) {
					PlayerComponent* player = static_cast<PlayerComponent*>(m_playerEntitys[3].getComponent(Types::Player));
					player->setMoveable(false);
				}
			}
		}
	}
	
	// check collision between player and Cheese
	searchCheese();
	for (Entity& goalEntity : m_goalEntitys) 
	{

		GoalComponent* goal = static_cast<GoalComponent*>(goalEntity.getComponent(Types::Goal));
		PositionComponent * goalPos = static_cast<PositionComponent*>(goalEntity.getComponent(Types::Position));
		// check is button on the map
		if (goal->getAlive()) 
		{

			CollisionComponent* goalCollider = static_cast<CollisionComponent*>(goalEntity.getComponent(Types::Collider));

			goalCollider->updateCollider(goalEntity);

			for (Entity& playerEntitys : m_playerEntitys) 
			{
				CollisionComponent* playerCollider = static_cast<CollisionComponent*>(playerEntitys.getComponent(Types::Collider));
				
				PlayerComponent* player = static_cast<PlayerComponent*>(playerEntitys.getComponent(Types::Player));
				PositionComponent* playerPos = static_cast<PositionComponent*>(playerEntitys.getComponent(Types::Position));
					if (checkCollision(goalCollider->getCircleCollider(), playerCollider->getPolyCollider()))
					{
						//std::cout << "Player with ID : " << player->getId() << "Collected the cheese" << std::endl;
						player->gainCheese(1);
						t_observer->onNotify(AudioObserver::PICKUPCHEESE);
						t_ps.push_back((new ParticleSystem(250, playerPos->getPositionX(), playerPos->getPositionY() , t_renderer,ParticleType::CheesePickup)));
						goal->setAlive(false);
					}
			}
		}
	}

	bombCollision(t_observer);

}

void CollisionSystem::bombCollision(AudioObserver* t_observer)
{
	for (Entity& bombEntity : m_bombEntitys) {
		BombComponent* bombComp = static_cast<BombComponent*>(bombEntity.getComponent(Types::Bomb));

		if (bombComp->getState() != BombState::Removed) {

			CollisionComponent* bombCollider = static_cast<CollisionComponent*>(bombEntity.getComponent(Types::Collider));

			for (Entity& playerEntity : m_playerEntitys) {

				CollisionComponent* playerCollider = static_cast<CollisionComponent*>(playerEntity.getComponent(Types::Collider));

				bombCollider->updateCollider(bombEntity);

				if (checkCollision(bombCollider->getCircleCollider(), playerCollider->getPolyCollider())) {

					PlayerComponent* playerComp = static_cast<PlayerComponent*>(playerEntity.getComponent(Types::Player));
					
					if (!playerComp->checkCarryBomb()) {

						if (bombComp->getState() == BombState::Explode) {
							playerComp->setDizzyState(true);
						}
						else if (bombComp->getState() != BombState::Activate) {
							bombComp->playerGetBomb(playerComp->getId());
							t_observer->onNotify(AudioObserver::PICKUPBOMB);
							playerComp->setInteract(false);
							playerComp->getABomb(true);

						}
					}
				}
			}
		}
	}
}


void CollisionSystem::tileCollision(CollisionComponent* playerCollider, PositionComponent* positionComp, Level& t_mazeWalls, AudioObserver* t_observer) {
	float x, y, width, height;
	for (int i = 0; i < t_mazeWalls.m_mazeWalls.size(); i++) {
		x = t_mazeWalls.m_mazeWalls[i].x;
		y = t_mazeWalls.m_mazeWalls[i].y;
		width = t_mazeWalls.m_mazeWalls[i].width;
		height = t_mazeWalls.m_mazeWalls[i].height;
		m_wallCollider.min = { x , y };
		m_wallCollider.max = { x + width , y + height };

		if (checkCollision(m_wallCollider, playerCollider->getPolyCollider())) {
			positionComp->backToPreviousePos();
		}
	}

	for (int i = 0; i < t_mazeWalls.m_outerBorders.size(); i++) {
		x = t_mazeWalls.m_outerBorders[i].x;
		y = t_mazeWalls.m_outerBorders[i].y;
		width = t_mazeWalls.m_outerBorders[i].width;
		height = t_mazeWalls.m_outerBorders[i].height;
		m_wallCollider.min = { x , y };
		m_wallCollider.max = { x + width , y + height };

		if (checkCollision(m_wallCollider, playerCollider->getPolyCollider())) {
			positionComp->backToPreviousePos();
		}
	}
}


void CollisionSystem::tileCollision(float x, float y, float width, float height, Level& t_mazeWalls,AudioObserver* t_observer)
{
	for (int i = 0; i < t_mazeWalls.m_mazeWalls.size(); i++)
	{
		//right of tile
		if (x <= t_mazeWalls.m_mazeWalls[i].x + t_mazeWalls.m_mazeWalls[i].width &&
			x >= t_mazeWalls.m_mazeWalls[i].x &&
			y + height >= t_mazeWalls.m_mazeWalls[i].y &&
			y <= t_mazeWalls.m_mazeWalls[i].y + t_mazeWalls.m_mazeWalls[i].height)
		{
			//std::cout << "right tile WALL collision!" << std::endl;
			m_positionComp->backToPreviousePos();
			//m_positionComp->setPosition(t_mazeWalls.m_mazeWalls[i].x + RAT_H, y);
		}

		//left of tile
		if (x + width >= t_mazeWalls.m_mazeWalls[i].x &&
			x + width < t_mazeWalls.m_mazeWalls[i].x + t_mazeWalls.m_mazeWalls[i].width &&
			y + height >= t_mazeWalls.m_mazeWalls[i].y &&
			y <= t_mazeWalls.m_mazeWalls[i].y + t_mazeWalls.m_mazeWalls[i].height)
		{
			//std::cout << "left tile WALL collision!" << std::endl;
			//m_positionComp->setPosition(t_mazeWalls.m_mazeWalls[i].x - RAT_W, y);
			m_positionComp->backToPreviousePos();
		}
		//top of tile
		if (y + height >= t_mazeWalls.m_mazeWalls[i].y &&
			y + height <= t_mazeWalls.m_mazeWalls[i].y + t_mazeWalls.m_mazeWalls[i].height &&
			x > t_mazeWalls.m_mazeWalls[i].x - width &&
			x <= t_mazeWalls.m_mazeWalls[i].x + t_mazeWalls.m_mazeWalls[i].width)
		{
			{
				//std::cout << "top tile WALL collision!" << std::endl;
				//m_positionComp->setPosition(x, t_mazeWalls.m_mazeWalls[i].y - RAT_H);
				m_positionComp->backToPreviousePos();
			}
		}
		//bottom of tile
		if (y >= t_mazeWalls.m_mazeWalls[i].y + t_mazeWalls.m_mazeWalls[i].height &&
			y <= t_mazeWalls.m_mazeWalls[i].y &&
			x > t_mazeWalls.m_mazeWalls[i].x - width &&
			x <= t_mazeWalls.m_mazeWalls[i].x + t_mazeWalls.m_mazeWalls[i].width)
		{
			{
				//std::cout << "bottom tile WALL collision!" << std::endl;
				//m_positionComp->setPosition(x, t_mazeWalls.m_mazeWalls[i].y + RAT_W);
				m_positionComp->backToPreviousePos();
			}
		}
	}

	/// <summary>
	///		Checking Outer Borders and Middle
	/// </summary>
	for (int i = 0; i < t_mazeWalls.m_outerBorders.size(); i++)
	{
		//right of tile
		if (x <= t_mazeWalls.m_outerBorders[i].x + t_mazeWalls.m_outerBorders[i].width &&
			x >= t_mazeWalls.m_outerBorders[i].x &&
			y + height >= t_mazeWalls.m_outerBorders[i].y &&
			y <= t_mazeWalls.m_outerBorders[i].y + t_mazeWalls.m_outerBorders[i].height)
		{
			//std::cout << "right tile WALL collision!" << std::endl;
			m_positionComp->backToPreviousePos();
			//m_positionComp->setPosition(t_mazeWalls.m_mazeWalls[i].x + RAT_H, y);
		}

		//left of tile
		if (x + width >= t_mazeWalls.m_outerBorders[i].x &&
			x + width < t_mazeWalls.m_outerBorders[i].x + t_mazeWalls.m_outerBorders[i].width &&
			y + height >= t_mazeWalls.m_outerBorders[i].y &&
			y <= t_mazeWalls.m_outerBorders[i].y + t_mazeWalls.m_outerBorders[i].height)
		{
			//std::cout << "left tile WALL collision!" << std::endl;
			//m_positionComp->setPosition(t_mazeWalls.m_mazeWalls[i].x - RAT_W, y);
			m_positionComp->backToPreviousePos();
		}
		//top of tile
		if (y + height >= t_mazeWalls.m_outerBorders[i].y &&
			y + height <= t_mazeWalls.m_outerBorders[i].y + t_mazeWalls.m_outerBorders[i].height &&
			x > t_mazeWalls.m_outerBorders[i].x - width &&
			x <= t_mazeWalls.m_outerBorders[i].x + t_mazeWalls.m_outerBorders[i].width)
		{
			{
				//std::cout << "top tile WALL collision!" << std::endl;
				//m_positionComp->setPosition(x, t_mazeWalls.m_mazeWalls[i].y - RAT_H);
				m_positionComp->backToPreviousePos();

			}
		}
		////bottom of tile
		if (y >= t_mazeWalls.m_outerBorders[i].y + t_mazeWalls.m_outerBorders[i].height &&
			y <= t_mazeWalls.m_outerBorders[i].y &&
			x > t_mazeWalls.m_outerBorders[i].x - width &&
			x <= t_mazeWalls.m_outerBorders[i].x + t_mazeWalls.m_outerBorders[i].width)
		{
			{
				//std::cout << "bottom tile WALL collision!" << std::endl;
				//m_positionComp->setPosition(x, t_mazeWalls.m_mazeWalls[i].y + RAT_W);
				m_positionComp->backToPreviousePos();

			}
		}
	}

	for (int i = 0; i < t_mazeWalls.m_teleport.size(); i++)
	{
		int random = rand() % 4;
		//right of tile
		if (x <= t_mazeWalls.m_teleport[i].x + t_mazeWalls.m_teleport[i].width &&
			x >= t_mazeWalls.m_teleport[i].x &&
			y + height >= t_mazeWalls.m_teleport[i].y &&
			y <= t_mazeWalls.m_teleport[i].y + t_mazeWalls.m_teleport[i].height)
		{
			t_observer->onNotify(AudioObserver::PORTAL);
			std::cout << "right TELEPORT collision!" << std::endl;
			m_positionComp->setPosition(t_mazeWalls.m_teleport[random].x + 60, t_mazeWalls.m_teleport[random].y);
		}

		//left of tile
		if (x + width >= t_mazeWalls.m_teleport[i].x &&
			x + width < t_mazeWalls.m_teleport[i].x + t_mazeWalls.m_teleport[i].width &&
			y + height >= t_mazeWalls.m_teleport[i].y &&
			y <= t_mazeWalls.m_teleport[i].y + t_mazeWalls.m_teleport[i].height
			)
		{
			t_observer->onNotify(AudioObserver::PORTAL);
			std::cout << "left TELEPORT collision!" << std::endl;
			m_positionComp->setPosition(t_mazeWalls.m_teleport[random].x + 60, t_mazeWalls.m_teleport[random].y);
		}
		//top of tile
		if (y + height >= t_mazeWalls.m_teleport[i].y &&
			y + height <= t_mazeWalls.m_teleport[i].y + t_mazeWalls.m_teleport[i].height &&
			x > t_mazeWalls.m_teleport[i].x - width &&
			x <= t_mazeWalls.m_teleport[i].x + t_mazeWalls.m_teleport[i].width
			)
		{
			t_observer->onNotify(AudioObserver::PORTAL);
			std::cout << "top TELEPORT collision!" << std::endl;
			m_positionComp->setPosition(t_mazeWalls.m_teleport[random].x + 60, t_mazeWalls.m_teleport[random].y );
		}
		////bottom of tile
		if (y >= t_mazeWalls.m_teleport[i].y + t_mazeWalls.m_teleport[i].height &&
			y <= t_mazeWalls.m_teleport[i].y &&
			x > t_mazeWalls.m_teleport[i].x - width &&
			x <= t_mazeWalls.m_teleport[i].x + t_mazeWalls.m_teleport[i].width)
		{
			t_observer->onNotify(AudioObserver::PORTAL);
			std::cout << "bottom TELEPORT collision!" << std::endl;
			m_positionComp->setPosition(t_mazeWalls.m_teleport[random].x+60, t_mazeWalls.m_teleport[random].y);
		}
	}
}

/// <summary>
/// search the vector entity and find all entity we need
/// </summary>
void CollisionSystem::searchEntities() {
	m_playerEntitys.clear();
	m_buttonEntitys.clear();
	m_trapEntitys.clear();
	m_doorEntitys.clear();
	m_bombEntitys.clear();

	for (Entity& e1 : entities) {
		//get the all player entities from entities vector
		if (e1.getType() == Types::Player)
		{
			m_playerEntitys.push_back(e1);
		}
		//get the all button entites from entities vector
		else if (e1.getType() == Types::Button)
		{
			m_buttonEntitys.push_back(e1);
		}
		//get the all trpa entites from entities vector
		else if (e1.getType() == Types::Traps)
		{
			m_trapEntitys.push_back(e1);
		}
		//get the all door entites from entities vector
		else if (e1.getType() == Types::Door)
		{
			m_doorEntitys.push_back(e1);
		}
		//get the all bomb entites from entities vector
		else if (e1.getType() == Types::Bomb)
		{
			m_bombEntitys.push_back(e1);
		}

	}
}

/// <summary>
/// check the collision between circle and rectangle
/// </summary>
/// <param name="t_collider"> circle collider</param>
/// <param name="t_otherCollider">rectangle collider</param>
/// <returns></returns>
bool CollisionSystem::checkCollision(c2Circle t_collider, c2AABB t_otherCollider)
{
	if (c2CircletoAABB(t_collider, t_otherCollider)) {
		//std::cout << "Collision" << std::endl;
		//handleCollision();
		return true;
	}
	return false;
}


/// <summary>
/// check the collision between circle and polygon
/// </summary>
/// <param name="t_collider"> circle collider</param>
/// <param name="t_otherCollider">rectangle collider</param>
/// <returns></returns>
bool CollisionSystem::checkCollision(c2Circle t_collider, c2Poly t_otherCollider)
{
	if (c2CircletoPoly(t_collider, &t_otherCollider, nullptr)) {
		//std::cout << "Collision" << std::endl;
		//handleCollision();
		return true;
	}
	return false;
}

/// <summary>
/// check the collision between rectangle and rectangle
/// </summary>
/// <param name="t_collider">rectangle collider</param>
/// <param name="t_otherCollider">rectangle collider</param>
/// <returns></returns>
bool CollisionSystem::checkCollision(c2AABB t_collider, c2AABB t_otherCollider)
{
	if (c2AABBtoAABB(t_collider, t_otherCollider)) {
		//std::cout << "Collision" << std::endl;
		//handleCollision();
		return true;
	}
	return false;
}

/// <summary>
/// check the collision between rectangle and polygon
/// </summary>
/// <param name="t_collider">rectangle collider</param>
/// <param name="t_otherCollider">polygon collider</param>
/// <returns></returns>
bool CollisionSystem::checkCollision(c2AABB t_collider, c2Poly t_otherCollider)
{
	if (c2AABBtoPoly(t_collider, &t_otherCollider, nullptr)) {
		//std::cout << "Collision" << std::endl;
		//handleCollision();
		return true;
	}
	return false;
}

void CollisionSystem::searchCheese()
{
	m_goalEntitys.clear();

	for (Entity& e1 : entities) {
		if (e1.getType() == Types::Goal)
		{
			m_goalEntitys.push_back(e1);
		}
	}
}

void CollisionSystem::TileBombCollision(Level* t_level, CollisionComponent* t_bomb)
{
	for (int i = 0; i < t_level->m_mazeWalls.size(); i++)
	{
		c2AABB tempCollider;

		tempCollider.min.x = t_level->m_mazeWalls[i].x;
		tempCollider.min.y = t_level->m_mazeWalls[i].y;
		
		tempCollider.max.x = t_level->m_mazeWalls[i].x + t_level->m_mazeWalls[i].width;
		tempCollider.max.y = t_level->m_mazeWalls[i].y + t_level->m_mazeWalls[i].height;

		if(checkCollision(t_bomb->getCircleCollider(), tempCollider))
		{
			for (int t = 0; t < t_level->tiles.size(); t++)
			{
				if (t_level->tiles[t].x == t_level->m_mazeWalls[i].x && t_level->tiles[t].y == t_level->m_mazeWalls[i].y)
				{
					t_level->tiles[t].alive = false;
				}
			}

			t_level->m_mazeWalls.erase(t_level->m_mazeWalls.begin() + i);
			
		}
	}
	/*if (checkCollision(bombCollider->getCircleCollider(), playerCollider->getAABBCollider())) {

		PlayerComponent* playerComp = static_cast<PlayerComponent*>(playerEntity.getComponent(Types::Player));

		if (bombComp->getState() == BombState::Explode) {
			playerComp->setDizzyState(true);
		}
		else {
			if (playerComp->getInteract()) {
				bombComp->playerGetBomb(playerComp->getId());
				t_observer->onNotify(AudioObserver::PICKUPBOMB);
				playerComp->setInteract(false);
			}
		}*/
}

