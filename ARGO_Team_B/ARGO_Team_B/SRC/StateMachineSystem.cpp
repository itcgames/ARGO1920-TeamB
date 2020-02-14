#include "StateMachineSystem.h"

StateMachineSystem::StateMachineSystem()
{
}

StateMachineSystem::~StateMachineSystem()
{
}

void StateMachineSystem::updateComponent(Component* c)
{
	for (Entity& e : entities)
	{
		//AnimatedSpriteComponent* animated = dynamic_cast<AnimatedSpriteComponent*>(e.getComponent(Types::AnimatedSprite));
		PositionComponent* pos = dynamic_cast<PositionComponent*>(e.getComponent(Types::Position));
		//if (animated != nullptr)
		//{
		//	animated->update();
		//	animated->render(pos->getPositionX(), pos->getPositionY());
		//}
	}
}

void StateMachineSystem::setCurrent()
{
}

void StateMachineSystem::setPrevious()
{
}
