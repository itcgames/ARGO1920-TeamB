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
		playerCollider.push_back(static_cast<CollisionComponent*>(player.getComponent(Types::Collider)));
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


bool CollisionSystem::checkCollision(c2Circle t_collider, c2Circle t_otherCollider)
{
	if (c2CircletoCircle(t_collider, t_otherCollider)) {
		std::cout << "Collision" << std::endl;
		//handleCollision();
		return true;
	}
	return false;
}

