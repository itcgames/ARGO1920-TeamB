#include "ButtonComponent.h"

/// <summary>
/// id is using for connect button and object
/// the type is using for door system
/// </summary>
/// <param name="init"></param>
/// <param name="id"></param>
/// <param name="type"></param>
ButtonComponent::ButtonComponent(bool init, int id, int type) {
	m_acitve = init;
	m_alive = true;

	m_redTeam = false;
	m_greenTeam = false;

	m_id = id;
	m_type = type;
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

int ButtonComponent::getType(){
	return m_type; 
}

bool ButtonComponent::getRedDoor() {
	return m_redTeam;
}

bool ButtonComponent::getGreenDoor() {
	return m_greenTeam;
}