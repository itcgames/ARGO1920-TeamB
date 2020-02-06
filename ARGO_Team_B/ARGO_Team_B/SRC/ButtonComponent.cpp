#include "ButtonComponent.h"

ButtonComponent::ButtonComponent(bool init, int id) {
	m_acitve = init;
	m_alive = true;
	m_id = id;
}

ButtonComponent::ButtonComponent(bool red, bool green, int id) {
	m_id = id;
	m_alive = true;

	m_redTeam = red;
	m_greenTeam = green;
}

ButtonComponent::~ButtonComponent() {

}


void ButtonComponent::setState(bool state) {
	m_acitve = state;
	m_alive = false;
}

void ButtonComponent::setRedDoor(bool state) {
	m_redTeam = state;
}

void ButtonComponent::setGreenDoor(bool state) {
	m_greenTeam = state;
}

bool ButtonComponent::getState() {
	return m_acitve;
}

bool ButtonComponent::getAlive() {
	return m_alive;
}

int ButtonComponent::getId() {
	return m_id;
}