#include "PlayerComponent.h"

PlayerComponent::PlayerComponent(int id) {
	m_id = id;
	m_moveable = true;
}

PlayerComponent::~PlayerComponent() {

}

void PlayerComponent::setMoveable(bool state) {
	m_moveable = state;
}

void PlayerComponent::setDizzyState(bool dizzy) {
	m_dizzy = dizzy;
}