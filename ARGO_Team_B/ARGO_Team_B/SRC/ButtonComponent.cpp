#include "../INCLUDE/ButtonComponent.h"

ButtonComponent::ButtonComponent(bool init, int id) {
	m_acitve = init;
	m_id = id;
}

ButtonComponent::~ButtonComponent() {

}


void ButtonComponent::setState(bool state) {
	m_acitve = state;
}

bool ButtonComponent::getState() {
	return m_acitve;
}