#include "../INCLUDE/ButtonComponent.h"

ButtonComponent::ButtonComponent(bool init) {
	m_acitve = init;
}

ButtonComponent::~ButtonComponent() {

}


void ButtonComponent::setState(bool state) {
	m_acitve = state;
}

bool ButtonComponent::getState() {
	return m_acitve;
}