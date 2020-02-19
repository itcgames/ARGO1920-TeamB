#include "StateMachineSystem.h"

StateMachineSystem::StateMachineSystem() :
	m_current{ new IdleState() }
{
}

StateMachineSystem::~StateMachineSystem()
{
}

void StateMachineSystem::updateComponent(Component* c)
{
	for (Entity& e : entities)
	{
		AnimatedSpriteComponent* animated = dynamic_cast<AnimatedSpriteComponent*>(e.getComponent(Types::AnimatedSprite));
		PositionComponent* pos = dynamic_cast<PositionComponent*>(e.getComponent(Types::Position));
		if (animated != nullptr)
		{
			animated->setCurrent(m_current);
			animated->update();
			animated->render(pos->getPositionX(), pos->getPositionY());
		}
	}
}

void StateMachineSystem::setCurrent(States t_state)
{
	for (Entity& e : entities)
	{
		AnimatedSpriteComponent* animated = dynamic_cast<AnimatedSpriteComponent*>(e.getComponent(Types::AnimatedSprite));
		if (animated != nullptr)
		{
			switch (t_state)
			{
			case States::Interact:
				m_current->interact(animated);
				break;
			case States::Attack:
				m_current->attack(animated);
				break;
			case States::Idle:
				m_current->idle(animated);
				break;
			case States::Stunned:
				m_current->stunned(animated);
				break;
			case States::Walking:
				m_current->walking(animated);
				break;
			default:
				break;
			}
		}
	}
	
}
