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
	PlayerComponent* playerComp = dynamic_cast<PlayerComponent*>(m_entity.getComponent(Types::Player));

	ControlComponent *control = dynamic_cast<ControlComponent*>(m_entity.getComponent(Types::Control));
	if (control != nullptr)
	{
		//control->controlDown(posComp, t_fsm);
		//control->controlDown(posComp, t_fsm);

		//control->controlUp(posComp, t_fsm);
		//control->controlUp(posComp, t_fsm);

	}
}

