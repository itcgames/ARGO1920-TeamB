#include "WalkingState.h"

#include "StunnedState.h"
#include "IdleState.h"
#include "AttackState.h"
#include "WalkWithBombState.h"
#include "EatCheeseState.h"

WalkingState::WalkingState()
{
	m_type = States::Walking;
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
void WalkingState::walkWithBomb(AnimatedSpriteComponent* t_a)
{
	std::cout << "Walking -> walkWithBomb" << std::endl;
	t_a->setCurrent(new WalkWithBombState());
	delete this;
}

void WalkingState::eatCheese(AnimatedSpriteComponent* t_a)
{
	std::cout << "Walking -> eatCheese" << std::endl;
	t_a->setCurrent(new EatCheeseState());
	delete this;
}
