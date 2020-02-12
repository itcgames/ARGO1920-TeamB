#include "BombSystem.h"

BombSystem::BombSystem() {

}

BombSystem::~BombSystem() {

}

void BombSystem::updateComponent(Component* component) {

}

void BombSystem::updateComponent(float dt) {
	searchEntities();

	for (Entity& bombEntity : m_bombEntitys) {
		BombComponent* bombComp = static_cast<BombComponent*>(bombEntity.getComponent(Types::Bomb));
		int ownerId = bombComp->bombOwner();

		if (bombComp->isPlayerOwnedBomb() && ownerId != 0) {
			PositionComponent* bombPos = static_cast<PositionComponent*>(bombEntity.getComponent(Types::Position));

			PositionComponent* playerPos = static_cast<PositionComponent*>(m_playerEntitys[ownerId].getComponent(Types::Position));

			bombPos->setPosition(playerPos->getPositionX(), playerPos->getPositionY());
		}

		/// <summary>
		/// if the bomb state change to activate then start count down
		/// when the timer less then 0, change the state to explode
		/// </summary>
		if (bombComp->getState() == BombState::Activate) {
			int timer = bombComp->getBombTimer();
			if (timer <= 0.0f) {
				bombComp->setState(BombState::Explode);
				CollisionComponent* bombCollider = static_cast<CollisionComponent*>(m_playerEntitys[ownerId].getComponent(Types::Bomb));
				bombCollider->setCircleRadius(bombComp->getBlastRadius());
			}
			timer -= dt;
			bombComp->setBombTimer(timer);
		}

	}
}

/// <summary>
/// search the vector entity and find all entity we need
/// </summary>
void BombSystem::searchEntities() {
	m_playerEntitys.clear();
	m_bombEntitys.clear();

	for (Entity& e1 : entities) {
		//get the all player entities from entities vector
		if (e1.getType() == Types::Player)
		{
			m_playerEntitys.push_back(e1);
		}
		//get the all button entites from entities vector
		else if (e1.getType() == Types::Bomb)
		{
			m_bombEntitys.push_back(e1);
		}

	}
}