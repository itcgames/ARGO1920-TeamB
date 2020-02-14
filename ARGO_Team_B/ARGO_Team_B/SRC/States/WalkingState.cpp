#include "WalkingState.h"

#include "StunnedState.h"
#include "IdleState.h"
#include "AttackState.h"

WalkingState::WalkingState()
{
}

WalkingState::~WalkingState()
{
}

void WalkingState::idle(AnimatedSpriteComponent* t_a)
{
	std::cout << "Walking -> Idle" << std::endl;
	t_a->setCurrent(new IdleState());
	delete this;
}

void WalkingState::stunned(AnimatedSpriteComponent* t_a)
{
	std::cout << "Walking -> stunned" << std::endl;
	t_a->setCurrent(new StunnedState());
	delete this;
}

void WalkingState::attack(AnimatedSpriteComponent* t_a)
{
	std::cout << "Walking -> attack" << std::endl;
	t_a->setCurrent(new AttackState());
	delete this;
}
