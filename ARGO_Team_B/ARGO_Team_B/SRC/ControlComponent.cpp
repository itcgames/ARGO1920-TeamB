#include "../INCLUDE/ControlComponent.h"

ControlComponent::ControlComponent(Entity & t_gameObject):
	m_entity(t_gameObject)
{
	m_compNum = s_controlID++;
	m_controller = new Xbox360Controller(m_compNum);
}

ControlComponent::~ControlComponent()
{
}

void ControlComponent::handleInput()
{
	PositionComponent* posComp = dynamic_cast<PositionComponent*>(m_entity.getComponent(Components::Position));
	if (posComp != nullptr)
	{
		m_controller->checkButton();
		

		if (m_controller->m_currentState.DpadUp) {
			posComp->moveUp();
		}

		if (m_controller->m_currentState.DpadLeft) {
			posComp->moveLeft();
		}

		if (m_controller->m_currentState.DpadRight) {
			posComp->moveRight();
		}

		if (m_controller->m_currentState.DpadDown) {
			posComp->moveDown();

		}
		
		m_controller->m_currentState.DpadUp = false;
		m_controller->m_currentState.DpadDown= false;
		m_controller->m_currentState.DpadLeft = false;
		m_controller->m_currentState.DpadRight = false;
	}
}

