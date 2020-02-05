#include "../INCLUDE/ControlComponent.h"

ControlComponent::ControlComponent()
{
	m_compNum = s_controlID++;
	m_controller = new Xbox360Controller(m_compNum);
}

ControlComponent::~ControlComponent()
{
}

void ControlComponent::handleInput(Component* t_position)
{
	PositionComponent* posComp = dynamic_cast<PositionComponent*>(t_position);
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
	}
}

