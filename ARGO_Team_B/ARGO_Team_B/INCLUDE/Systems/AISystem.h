#ifndef AI_SYSTEM
#define AI_SYSTEM

#include <SDL.h>
#include "System.h"
#include "TestBotBehaviourComponent.h"
#include "StateMachineSystem.h"

class AISystem : public System
{
public:
	AISystem();
	AISystem(StateMachineSystem* t_fsm);
	~AISystem();
	void updateComponent(Component* component) override;
private:
	StateMachineSystem m_FSM;
};

#endif // !AI_SYSTEM
