#include "InteractState.h"

#include "IdleState.h"
#include "WalkingState.h"
#include "AttackState.h"

InteractState::InteractState()
{
	m_type = States::Interact;
}

InteractState::~InteractState()
{
}

void InteractState::walking(AnimatedSpriteComponent* t_a)
{
	std::cout << "Interact -> Walking" << std::endl;
	t_a->setCurrent(new WalkingState());
	delete this;
}

void InteractState::attack(AnimatedSpriteComponent* t_a)
{
	std::cout << "Interact -> attack" << std::endl;
	t_a->setCurrent(new AttackState());
	delete this;
}

void InteractState::idle(AnimatedSpriteComponent* t_a)
{
	std::cout << "Interact -> Idle " << std::endl;
	t_a->setCurrent(new IdleState());
	delete this;
}
