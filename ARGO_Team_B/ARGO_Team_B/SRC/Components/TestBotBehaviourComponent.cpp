#include "TestBotBehaviourComponent.h"

TestBotBehaviourComponent::TestBotBehaviourComponent(Entity& t_gameObject) :
	m_entity{ t_gameObject }
{
}

TestBotBehaviourComponent::~TestBotBehaviourComponent()
{
}

void TestBotBehaviourComponent::update()
{
	PositionComponent* pos = dynamic_cast<PositionComponent*>(m_entity.getComponent(Types::Position));
	if (pos != nullptr)
	{
		pos->moveDown();
		pos->moveDown();
		pos->moveLeft();
		pos->moveLeft();
		pos->moveUp();
		pos->moveUp();
		pos->moveRight();
		pos->moveRight();
	}
}

