#include "BombComponent.h"

BombComponent::BombComponent() {
	setState(BombState::Idle);

	m_timer = 5.0f;
	m_owned = false;
	m_ownerId = 0;
	blastRadius = 100.0f;
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
}