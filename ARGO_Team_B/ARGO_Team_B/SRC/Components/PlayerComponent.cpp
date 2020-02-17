#include "PlayerComponent.h"

PlayerComponent::PlayerComponent(int id) {
	m_id = id;
	m_moveable = true;
	m_interact = false;
	m_swipeCooldown = 0.5f;
	m_dizzy = false;
}

PlayerComponent::~PlayerComponent() {

}

void PlayerComponent::setMoveable(bool state) {
	m_moveable = state;
}

void PlayerComponent::setDizzyState(bool dizzy) {
	m_dizzy = dizzy;
}

void PlayerComponent::setInteract(bool interact)
{
	m_interact = interact;
}

void PlayerComponent::setSwipeCooldown(float time)
{
	m_swipeCooldown = time;
}

void PlayerComponent::gainCheese(int num)
{
	m_cheese += num;
}
