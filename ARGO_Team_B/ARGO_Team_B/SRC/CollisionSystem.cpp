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

void CollisionSystem::updateComponent() {
	searchPlayer();

	vector<CollisionComponent*> playerCollider;
	for (Entity& player : m_playerEntitys) {
		CollisionComponent* playerComp = dynamic_cast<CollisionComponent*>(player.getComponent(Types::Collider));
		playerComp->updateCollider(player);
		playerCollider.push_back(playerComp);
		
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

			for (Entity& playerEntitys : m_playerEntitys) {
				CollisionComponent* playerCollision = static_cast<CollisionComponent*>(playerEntitys.getComponent(Types::Collider));

				PlayerComponent* player = static_cast<PlayerComponent*>(playerEntitys.getComponent(Types::Player));
				
				// check for 2 different button, 1 for trap button, 2 for door button
				switch (button->getType())
				{
				case 1:
					if (checkCollision(playerCollision->getCollider(), buttonCollider->getCollider())) {

						button->setState(true);
					}
					break;
				case 2:
					if (checkCollision(playerCollision->getCollider(), buttonCollider->getCollider())) {
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

	// check collision between player and door
	searchDoor();
	for (Entity& doorEntity : m_doorEntitys) {
		DoorComponent* door = static_cast<DoorComponent*>(doorEntity.getComponent(Types::Door));

		// if the door not open for two team, check collision
		if (!door->getGreenDoor() || !door->getRedDoor()) {

			CollisionComponent* doorCollider = static_cast<CollisionComponent*>(doorEntity.getComponent(Types::Collider));

			doorCollider->updateCollider(doorEntity);

			// red door open, check with player 1 and 3
			if (!door->getRedDoor()) {
				if (checkCollision(playerCollider[0]->getCollider(), doorCollider->getCollider())) {
					PlayerComponent* player = static_cast<PlayerComponent*>(m_playerEntitys[0].getComponent(Types::Player));
					player->setMoveable(false);
				}

				if (checkCollision(playerCollider[2]->getCollider(), doorCollider->getCollider())) {
					PlayerComponent* player = static_cast<PlayerComponent*>(m_playerEntitys[2].getComponent(Types::Player));
					player->setMoveable(false);
				}
			}

			// green door open, check with player 2 and 4
			if (!door->getGreenDoor()) {
				if (checkCollision(playerCollider[1]->getCollider(), doorCollider->getCollider())) {
					PlayerComponent* player = static_cast<PlayerComponent*>(m_playerEntitys[1].getComponent(Types::Player));
					player->setMoveable(false);
				}

				if (checkCollision(playerCollider[3]->getCollider(), doorCollider->getCollider())) {
					PlayerComponent* player = static_cast<PlayerComponent*>(m_playerEntitys[3].getComponent(Types::Player));
					player->setMoveable(false);
				}
			}
		}
	}
}

/// <summary>
/// get the all player entities from entities vector
/// </summary>
void CollisionSystem::searchPlayer() {
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
/// get the all trpa entites from entities vector
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

/// <summary>
/// get the all door entites from entities vector
/// </summary>
void CollisionSystem::searchDoor() {
	m_doorEntitys.clear();

	for (Entity& e1 : entities) {
		if (e1.getType() == Types::Door)
		{
			m_doorEntitys.push_back(e1);
		}
	}
}


bool CollisionSystem::checkCollision(c2Circle t_collider, c2Circle t_otherCollider)
{
	if (c2CircletoCircle(t_collider, t_otherCollider)) {
		std::cout << "Collision" << std::endl;
		//handleCollision();
		return true;
	}
	return false;
}



