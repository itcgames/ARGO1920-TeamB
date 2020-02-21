#include "BombComponent.h"

BombComponent::BombComponent() {
	setState(BombState::Activate);

	m_timer = 3.0f;
	m_owned = false;
	m_ownerId = 0;
	blastRadius = 75.0f;
	m_explosionTimer = 1.0f;
}

BombComponent::~BombComponent() {

}

void BombComponent::setState(BombState state) {
	m_currentState = state;
}

void BombComponent::playerGetBomb(int id) {
	m_owned = true;
	m_ownerId = id;
}

void BombComponent::playerPlaceBomb() {
	m_owned = false;
	m_ownerId = 0;
	setState(BombState::Activate);
}