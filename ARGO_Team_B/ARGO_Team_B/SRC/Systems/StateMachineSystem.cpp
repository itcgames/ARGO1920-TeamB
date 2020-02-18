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
		if (e.getEntityType() == EntityType::Rat)
		{

			AnimatedSpriteComponent* animated = dynamic_cast<AnimatedSpriteComponent*>(e.getComponent(Types::AnimatedSprite));
			PositionComponent* pos = dynamic_cast<PositionComponent*>(e.getComponent(Types::Position));
			if (animated != nullptr)
			{
				//animated->setCurrent(m_current);
				animated->update();
				animated->render(pos->getPositionX(), pos->getPositionY(), pos->getangle());
			}
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
			if (m_current == NULL) {
				m_current = new State();
			}
			switch (t_state)
			{
			case States::Interact:
				m_current->interact(animated);
				m_current = new InteractState();
				break;
			case States::Attack:
				m_current->attack(animated);
				m_current = new AttackState();
				break;
			case States::Idle:
				m_current->idle(animated);
				m_current = new IdleState();
				break;
			case States::Stunned:
				m_current->stunned(animated);
				m_current = new StunnedState();
				break;
			case States::Walking:
				m_current->walking(animated);
				m_current = new WalkingState();
				break;
			default:
				break;
			}
		}
	}
	
}
