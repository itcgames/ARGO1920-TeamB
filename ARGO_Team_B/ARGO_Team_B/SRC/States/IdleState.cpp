#include "IdleState.h"


void IdleState::walking(AnimatedSpriteComponent* t_a)
{
	std::cout << "Idle -> Walking" << std::endl;
	t_a->setCurrent(new WalkingState());
	delete this;
}

void IdleState::stunned(AnimatedSpriteComponent* t_a)
{
	std::cout << "Idle -> stunned" << std::endl;
	t_a->setCurrent(new StunnedState());
	delete this;
}

void IdleState::attack(AnimatedSpriteComponent* t_a)
{
	std::cout << "Idle -> attack" << std::endl;
	t_a->setCurrent(new AttackState());
	delete this;
}

void IdleState::interact(AnimatedSpriteComponent* t_a)
{
	std::cout << "Idle -> interact" << std::endl;
	t_a->setCurrent(new InteractState());
	delete this;
}