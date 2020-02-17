#pragma once

#include "System.h"
#include "AnimatedSpriteComponent.h"
#include "PositionComponent.h"
#include "Enums.h"
#include "AttackState.h"
#include "IdleState.h"
#include "InteractState.h"
#include "StunnedState.h"
#include "WalkingState.h"

class StateMachineSystem : public System
{
private:
	State* m_current;

public:
	StateMachineSystem();
	~StateMachineSystem();

	void updateComponent(Component* c) override;

	void setCurrent(States t_state);
};
