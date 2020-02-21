#include "AISystem.h"

AISystem::AISystem()
{
}

AISystem::AISystem(StateMachineSystem* t_fsm) 
{ 
	m_FSM = *t_fsm; 
}



AISystem::~AISystem() {}

void AISystem::updateComponent(Component* component)
{
	for (Entity& e : entities)
	{
		TestBotBehaviourComponent* bot = dynamic_cast<TestBotBehaviourComponent*>(e.getComponent(Types::TestBot));
		if (bot != nullptr)
		{
			bot->update(m_FSM);
		}
	}
}