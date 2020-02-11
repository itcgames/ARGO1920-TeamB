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
	searchPlayer();

	vector<CollisionComponent*> playerCollider;

	for (Entity& player : m_playerEntitys) {
		playerCollider.push_back(static_cast<CollisionComponent*>(player.getComponent(Types::Collider)));
		m_positionComp = static_cast<PositionComponent*>(player.getComponent(Types::Position));
		x1 = m_positionComp->getPositionX();
		y1 = m_positionComp->getPositionY();
		tileCollision(x1, y1, RAT_W, RAT_H, t_level);
	}

	// player 1 and player 2 collision check
	if (checkCollision(playerCollider[0]->getCollider(), playerCollider[1]->getCollider())) {

	}

	// player 3 and player 4 collision check
	if (checkCollision(playerCollider[2]->getCollider(), playerCollider[3]->getCollider())) {

	}


	// check collision between player and button
	searchButton();

	for (Entity& buttonEntity : m_buttonEntitys) {
		ButtonComponent* button = static_cast<ButtonComponent*>(buttonEntity.getComponent(Types::Button));
		// check is button on the map
		if (button->getAlive()) {

			CollisionComponent* buttonCollider = static_cast<CollisionComponent*>(buttonEntity.getComponent(Types::Collider));

			// update the component state **necessaey update**
			buttonCollider->updateCollider(buttonEntity);

			for (CollisionComponent* player : playerCollider) {


				if (checkCollision(player->getCollider(), buttonCollider->getCollider())) {

					button->setState(true);
				}
			}
		}
	}

	// check collision between player and traps
	searchTrap();
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
				if (playerHealth->getAlive()) {
					if (checkCollision(player->getCollider(), trapCollider->getCollider()) ) {
						cout << "player die" << endl;


						playerHealth->dead();
					}
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
					if (checkCollision(playerCollider->getCollider(), goalCollider->getCollider()))
					{
						std::cout << "Player with ID : " << player->getId() << "Collected the cheese" << std::endl;
						goal->setAlive(false);
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
/// get the all player entities from entities vector
/// </summary>
void CollisionSystem::searchPlayer() 
{
	m_playerEntitys.clear();

	for (Entity& e1 : entities) {
		if (e1.getType() == Types::Player)
		{
			m_playerEntitys.push_back(e1);
		}
	}
}

/// <summary>
/// get the all button entites from entities vector
/// </summary>
void CollisionSystem::searchButton() {
	m_buttonEntitys.clear();

	for (Entity& e1 : entities) {
		if (e1.getType() == Types::Button)
		{
			m_buttonEntitys.push_back(e1);
		}
	}
}

/// <summary>
/// get the all button entites from entities vector
/// </summary>
void CollisionSystem::searchTrap() {
	m_trapEntitys.clear();

	for (Entity& e1 : entities) {
		if (e1.getType() == Types::Traps)
		{
			m_trapEntitys.push_back(e1);
		}
	}
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


bool CollisionSystem::checkCollision(c2Circle t_collider, c2Circle t_otherCollider)
{
	if (c2CircletoCircle(t_collider, t_otherCollider)) {
		//std::cout << "Collision" << std::endl;
		//handleCollision();
		return true;
	}
	return false;
}

