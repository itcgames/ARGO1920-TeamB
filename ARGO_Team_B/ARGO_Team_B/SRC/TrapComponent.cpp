#include "..//INCLUDE/TrapComponent.h"

TrapComponent::TrapComponent(bool init) {
	m_alive = init;
}

TrapComponent::~TrapComponent() {

}

void TrapComponent::setState(bool state) {
	m_alive = state;
}