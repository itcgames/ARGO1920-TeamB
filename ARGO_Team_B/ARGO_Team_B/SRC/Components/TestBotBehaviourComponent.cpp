#include "TestBotBehaviourComponent.h"

TestBotBehaviourComponent::TestBotBehaviourComponent(Entity& t_gameObject) :
	m_entity{ t_gameObject }
{
}

TestBotBehaviourComponent::~TestBotBehaviourComponent()
{
}

void TestBotBehaviourComponent::update(StateMachineSystem& t_fsm)
{
	PositionComponent* posComp = dynamic_cast<PositionComponent*>(m_entity.getComponent(Types::Position));
	ControlComponent *control = dynamic_cast<ControlComponent*>(m_entity.getComponent(Types::Control));
	if (control != nullptr)
	{

		control->controlLeft(posComp);


		control->controlRight(posComp);
	}
}

