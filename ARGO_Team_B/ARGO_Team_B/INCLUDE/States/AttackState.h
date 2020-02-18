#pragma once

#include "State.h"


class AttackState : public State
{
public:
	AttackState();
	~AttackState();

	void stunned(AnimatedSpriteComponent* t_a) override;

	void idle(AnimatedSpriteComponent* t_a) override;
};
