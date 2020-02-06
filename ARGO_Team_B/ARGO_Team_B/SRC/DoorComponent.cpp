#include "../INCLUDE/DoorComponent.h"

DoorComponent::DoorComponent(int id) {
	m_id = id;
}

DoorComponent::~DoorComponent() {

}

void DoorComponent::setState(bool red, bool green) {
	m_redOpen = red;
	m_greenOpen = green;
}