#include "ControlComponent.h"

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
	RenderComponent* renderComp = dynamic_cast<RenderComponent*>(m_entity.getComponent(Types::Render));
	PositionComponent* posComp = dynamic_cast<PositionComponent*>(m_entity.getComponent(Types::Position));
	if (posComp != nullptr)
	{
		m_controller->checkButton();
		

		if (m_controller->m_currentState.LeftThumbStick.y < -m_controller->dpadThreshold) {
			p_walkUp = new WalkUpCommand();
			p_walkUp->execute(m_entity);
			renderComp->setAngle(270);
		}

		if ( m_controller->m_currentState.LeftThumbStick.x < -m_controller->dpadThreshold) {
			p_walkLeft = new WalkLeftCommand();
			p_walkLeft->execute(m_entity);
			renderComp->setAngle(180);
		}

		if (m_controller->m_currentState.LeftThumbStick.x > m_controller->dpadThreshold) {
			p_walkRight = new WalkRightCommand();
			p_walkRight->execute(m_entity);
			renderComp->setAngle(0);
		}

		if (m_controller->m_currentState.LeftThumbStick.y > m_controller->dpadThreshold) {
			p_walkDown= new WalkDownCommand();
			p_walkDown->execute(m_entity);
			renderComp->setAngle(90);
		}
		
		m_controller->m_currentState.DpadUp = false;
		m_controller->m_currentState.DpadDown= false;
		m_controller->m_currentState.DpadLeft = false;
		m_controller->m_currentState.DpadRight = false;
		m_controller->m_currentState.LeftThumbStick.x = 0;
		m_controller->m_currentState.LeftThumbStick.y = 0;
	}
}

