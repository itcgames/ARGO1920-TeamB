#include "PlayerComponent.h"

PlayerComponent::PlayerComponent(int id) {
	m_id = id;
	m_moveable = true;
	m_interact = false;
	m_swipeCooldown = 0.5f;
	m_dizzy = false;
	m_getACheese = false;
	m_cheese = 0;
	m_alive = false;
	m_carryABomb = false;
	m_dizzyTime = 3.0f;
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
	m_getACheese = true;
}

void PlayerComponent::setGetCheeseOff()
{
	m_getACheese = false;
}

bool PlayerComponent::getACheese()
{
	return m_getACheese;
}

void PlayerComponent::getABomb(bool state)
{
	m_carryABomb = state;
}

void PlayerComponent::setDizzyTime(float time)
{
	m_dizzyTime = time;
}

void PlayerComponent::reset()
{
	m_interact = false;
	m_swipeCooldown = 0.5f;
	m_dizzy = false;
	m_getACheese = false;
	m_cheese = 0;
	m_carryABomb = false;
}
