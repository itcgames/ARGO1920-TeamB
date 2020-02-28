#include "WalkWithBombState.h"

#include "StunnedState.h"
#include "IdleState.h"
#include "AttackState.h"
#include "EatCheeseState.h"
WalkWithBombState::WalkWithBombState()
{
	m_type = States::WalkingBomb;
}

WalkWithBombState::~WalkWithBombState()
{
}

void WalkWithBombState::idle(AnimatedSpriteComponent* t_a)
{
	std::cout << "WalkingWithBomb -> Idle" << std::endl;
	t_a->setCurrent(new IdleState());
	delete this;
}

void WalkWithBombState::stunned(AnimatedSpriteComponent* t_a)
{
	std::cout << "WalkingWithBomb -> stunned" << std::endl;
	t_a->setCurrent(new StunnedState());
	delete this;
}

void WalkWithBombState::attack(AnimatedSpriteComponent* t_a)
{
	std::cout << "WalkingWithBomb -> attack" << std::endl;
	t_a->setCurrent(new AttackState());
	delete this;
}
void WalkWithBombState::walking(AnimatedSpriteComponent* t_a)
{
	std::cout << "WalkingWithBomb -> walking" << std::endl;
	t_a->setCurrent(new AttackState());
	delete this;
}
void WalkWithBombState::eatCheese(AnimatedSpriteComponent* t_a)
{
	std::cout << "Walking -> eatCheese" << std::endl;
	t_a->setCurrent(new EatCheeseState());
	delete this;
}