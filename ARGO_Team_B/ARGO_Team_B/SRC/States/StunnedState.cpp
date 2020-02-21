#include "StunnedState.h"

#include "WalkingState.h"
#include "IdleState.h"

StunnedState::StunnedState()
{
	m_type = States::Stunned;
}

StunnedState::~StunnedState()
{
}

void StunnedState::walking(AnimatedSpriteComponent* t_a)
{
	std::cout << "Stunned -> Walking" << std::endl;
	t_a->setCurrent(new WalkingState());
	delete this;
}

void StunnedState::idle(AnimatedSpriteComponent* t_a)
{
	std::cout << "Stunned -> idle" << std::endl;
	t_a->setCurrent(new IdleState());
}
