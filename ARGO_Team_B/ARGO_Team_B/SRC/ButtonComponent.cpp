#include "ButtonComponent.h"

ButtonComponent::ButtonComponent(bool init, int id) {
	m_acitve = init;
	m_alive = true;
	m_id = id;
}

ButtonComponent::~ButtonComponent() {

}


void ButtonComponent::setState(bool state) {
	m_acitve = state;
	m_alive = false;
}

bool ButtonComponent::getState() {
	return m_acitve;
}

bool ButtonComponent::getAlive() {
	return m_alive;
}