#include "TrapComponent.h"

TrapComponent::TrapComponent(bool init, int id) {
	m_alive = init;
	m_id = id;
}

TrapComponent::~TrapComponent() {

}

void TrapComponent::setState(bool state) {
	m_alive = state;
}