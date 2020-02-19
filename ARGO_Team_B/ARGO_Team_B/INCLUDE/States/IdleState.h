#pragma once
#include "State.h"

#include "StunnedState.h"
#include "WalkingState.h"
#include "AttackState.h"
#include "InteractState.h"

class IdleState : public State
{
public:
	IdleState() { m_type = States::Idle; }
	~IdleState() {}

	void walking(AnimatedSpriteComponent* t_a) override;


	void stunned(AnimatedSpriteComponent* t_a) override;

	void attack(AnimatedSpriteComponent* t_a)override;

	void interact(AnimatedSpriteComponent* t_a)override;
};

