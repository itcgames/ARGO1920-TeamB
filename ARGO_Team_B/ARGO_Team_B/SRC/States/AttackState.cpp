#include "AttackState.h"

#include "IdleState.h"
#include "StunnedState.h"

AttackState::AttackState()
{
}

AttackState::~AttackState()
{
}

void AttackState::stunned(AnimatedSpriteComponent* t_a)
{
	std::cout << "Attack -> stunned" << std::endl;
	t_a->setCurrent(new StunnedState());
	delete this;
}

void AttackState::idle(AnimatedSpriteComponent* t_a)
{
	std::cout << "attack -> Idle" << std::endl;
	t_a->setCurrent(new IdleState());
	delete this;
}