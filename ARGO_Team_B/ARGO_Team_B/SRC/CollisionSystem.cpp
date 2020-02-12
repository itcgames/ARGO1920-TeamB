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

void CollisionSystem::updateComponent(Level& t_level)
{
	searchEntities();

	vector<CollisionComponent*> playerColliders;

	for (Entity& player : m_playerEntitys) {
		CollisionComponent* playerComp = dynamic_cast<CollisionComponent*>(player.getComponent(Types::Collider));
		playerComp->updateCollider(player);
		playerColliders.push_back(playerComp);
		
		m_positionComp = static_cast<PositionComponent*>(player.getComponent(Types::Position));
		x1 = m_positionComp->getPositionX();
		y1 = m_positionComp->getPositionY();
		tileCollision(x1, y1, RAT_W, RAT_H, t_level);
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
					if (checkCollision(playerCollision->getAABBCollider(), buttonCollider->getAABBCollider())) {

						button->setState(true);
					}
					break;
				case 2:
					if (checkCollision(playerCollision->getAABBCollider(), buttonCollider->getAABBCollider())) {
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
					if (checkCollision( player->getAABBCollider(), trapCollider->getPolyCollider()) ) {
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
				if (checkCollision(playerColliders[0]->getAABBCollider(), doorCollider->getAABBCollider())) {
					PlayerComponent* player = static_cast<PlayerComponent*>(m_playerEntitys[0].getComponent(Types::Player));
					player->setMoveable(false);
				}

				if (checkCollision(playerColliders[2]->getAABBCollider(), doorCollider->getAABBCollider())) {
					PlayerComponent* player = static_cast<PlayerComponent*>(m_playerEntitys[2].getComponent(Types::Player));
					player->setMoveable(false);
				}
			}

			// green door open, check with player 2 and 4
			if (!door->getGreenDoor()) {
				if (checkCollision(playerColliders[1]->getAABBCollider(), doorCollider->getAABBCollider())) {
					PlayerComponent* player = static_cast<PlayerComponent*>(m_playerEntitys[1].getComponent(Types::Player));
					player->setMoveable(false);
				}

				if (checkCollision(playerColliders[3]->getAABBCollider(), doorCollider->getAABBCollider())) {
					PlayerComponent* player = static_cast<PlayerComponent*>(m_playerEntitys[3].getComponent(Types::Player));
					player->setMoveable(false);
				}
			}
		}
	}

	// check collision between player and traps
	searchCheese();
	for (Entity& goalEntity : m_goalEntitys) 
	{

		GoalComponent* goal = static_cast<GoalComponent*>(goalEntity.getComponent(Types::Goal));

		// check is button on the map
		if (goal->getAlive()) 
		{

			CollisionComponent* goalCollider = static_cast<CollisionComponent*>(goalEntity.getComponent(Types::Collider));

			goalCollider->updateCollider(goalEntity);

			for (Entity& playerEntitys : m_playerEntitys) 
			{
				CollisionComponent* playerCollider = static_cast<CollisionComponent*>(playerEntitys.getComponent(Types::Collider));
				
				PlayerComponent* player = static_cast<PlayerComponent*>(playerEntitys.getComponent(Types::Player));
					if (checkCollision(goalCollider->getAABBCollider(), playerCollider->getAABBCollider()))
					{
						std::cout << "Player with ID : " << player->getId() << "Collected the cheese" << std::endl;
						goal->setAlive(false);
					}
			}
		}
	}

	bombCollision();
}

void CollisionSystem::bombCollision()
{
	for (Entity& bombEntity : m_bombEntitys) {
		BombComponent* bombComp = static_cast<BombComponent*>(bombEntity.getComponent(Types::Bomb));

		if (bombComp->getState() != BombState::Removed) {

			CollisionComponent* bombCollider = static_cast<CollisionComponent*>(bombEntity.getComponent(Types::Collider));

			for (Entity& playerEntity : m_playerEntitys) {

				CollisionComponent* playerCollider = static_cast<CollisionComponent*>(playerEntity.getComponent(Types::Collider));

				bombCollider->updateCollider(bombEntity);

				if (checkCollision(bombCollider->getCircleCollider(), playerCollider->getAABBCollider())) {

					PlayerComponent* playerComp = static_cast<PlayerComponent*>(playerEntity.getComponent(Types::Player));
					
					if (bombComp->getState() == BombState::Explode) {
						playerComp->setDizzyState(true);
					}
					else {
						bombComp->playerGetBomb(playerComp->getId());
					}
				}
			}

		}
	}
}


void CollisionSystem::tileCollision(float x, float y, float width, float height, Level& t_mazeWalls)
{
	for (int i = 0; i < t_mazeWalls.m_mazeWalls.size(); i++)
	{
		//right of tile
		if (x <= t_mazeWalls.m_mazeWalls[i].x + t_mazeWalls.m_mazeWalls[i].width &&
			x >= t_mazeWalls.m_mazeWalls[i].x &&
			y + height >= t_mazeWalls.m_mazeWalls[i].y &&
			y <= t_mazeWalls.m_mazeWalls[i].y + t_mazeWalls.m_mazeWalls[i].height)
		{
			std::cout << "right collision!" << std::endl;
			m_positionComp->setPosition(m_positionComp->getLastX(), m_positionComp->getLastY());
			//m_positionComp->setPosition(t_mazeWalls.m_mazeWalls[i].x + RAT_H, y);
		}

		//left of tile
		if (x + width >= t_mazeWalls.m_mazeWalls[i].x &&
			x + width < t_mazeWalls.m_mazeWalls[i].x + t_mazeWalls.m_mazeWalls[i].width &&
			y + height >= t_mazeWalls.m_mazeWalls[i].y &&
			y <= t_mazeWalls.m_mazeWalls[i].y + t_mazeWalls.m_mazeWalls[i].height)
		{
			std::cout << "left collision!" << std::endl;
			//m_positionComp->setPosition(t_mazeWalls.m_mazeWalls[i].x - RAT_W, y);
			m_positionComp->setPosition(m_positionComp->getLastX(), m_positionComp->getLastY());
		}
		//top of tile
		if (y + height >= t_mazeWalls.m_mazeWalls[i].y &&
			y + height <= t_mazeWalls.m_mazeWalls[i].y + t_mazeWalls.m_mazeWalls[i].height &&
			x > t_mazeWalls.m_mazeWalls[i].x - width &&
			x <= t_mazeWalls.m_mazeWalls[i].x + t_mazeWalls.m_mazeWalls[i].width)
		{
			{
				std::cout << "top collision!" << std::endl;
				//m_positionComp->setPosition(x, t_mazeWalls.m_mazeWalls[i].y - RAT_H);
				m_positionComp->setPosition(m_positionComp->getLastX(), m_positionComp->getLastY());

			}
		}
		////bottom of tile
		if (y>=t_mazeWalls.m_mazeWalls[i].y+t_mazeWalls.m_mazeWalls[i].height &&
			y<=t_mazeWalls.m_mazeWalls[i].y &&
			x > t_mazeWalls.m_mazeWalls[i].x - width &&
			x <= t_mazeWalls.m_mazeWalls[i].x + t_mazeWalls.m_mazeWalls[i].width)
		{
			{
				std::cout << "bottom collision!" << std::endl;
				//m_positionComp->setPosition(x, t_mazeWalls.m_mazeWalls[i].y + RAT_W);
				m_positionComp->setPosition(m_positionComp->getLastX(), m_positionComp->getLastY());

			}
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
		std::cout << "Collision" << std::endl;
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
		std::cout << "Collision" << std::endl;
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
		std::cout << "Collision" << std::endl;
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