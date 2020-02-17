#include "DoorComponent.h"

DoorComponent::DoorComponent(int id) {
	m_id = id;
	m_redOpen = false;
	m_greenOpen = false;
}

DoorComponent::~DoorComponent() {

}

void DoorComponent::setState(bool red, bool green) {
	m_redOpen = red;
	m_greenOpen = green;
}