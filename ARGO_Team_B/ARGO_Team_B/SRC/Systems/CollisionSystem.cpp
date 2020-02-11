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

	/*for (Component* collider1 : m_playerEntitys[0].getComponents()) {
		CollisionComponent* player1Collider = dynamic_cast<ButtonComponent*>(c1);
	}*/

	CollisionComponent* player1Collider = static_cast<CollisionComponent*>(m_playerEntitys[0].getComponent(Types::Collider));
	CollisionComponent* player2Collider = static_cast<CollisionComponent*>(m_playerEntitys[1].getComponent(Types::Collider));
	CollisionComponent* player3Collider = static_cast<CollisionComponent*>(m_playerEntitys[2].getComponent(Types::Collider));
	CollisionComponent* player4Collider = static_cast<CollisionComponent*>(m_playerEntitys[3].getComponent(Types::Collider));

	// player 1 and player 2 collision check
	checkCollision(player1Collider->getCollider(), player2Collider->getCollider());

	// player 3 and player 4 collision check
	checkCollision(player3Collider->getCollider(), player4Collider->getCollider());
}

void CollisionSystem::searchPlayer() {
	Entity m_player;

	for (Entity& e1 : entities) {
		if (e1.getType() == Types::Player)
		{
			m_playerEntitys.push_back(e1);
		}


		/*for (Component* c1 : e1.getComponents()) {
			PlayerComponent* playerComp = dynamic_cast<PlayerComponent*>(c1);
			if (playerComp != nullptr) {

				for (Entity& player : playerList) {
					if (player.getId() != m_player.getId()) {
						m_player = e1;
					}
					else {
						break;
					}
				}
				break;
			}
		}*/
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

