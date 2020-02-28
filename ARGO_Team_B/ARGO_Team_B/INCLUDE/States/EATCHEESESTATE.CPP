#include "EatCheeseState.h"

#include "WalkingState.h"
#include "IdleState.h"
#include "WalkWithBombState.h"
EatCheeseState::EatCheeseState()
{
	m_type = States::EatCheese;
}

EatCheeseState::~EatCheeseState()
{
}

void EatCheeseState::idle(AnimatedSpriteComponent* t_a)
{
	std::cout << "EatCheese -> Idle" << std::endl;
	t_a->setCurrent(new IdleState());
	delete this;
}
void EatCheeseState::walkWithBomb(AnimatedSpriteComponent* t_a)
{
	std::cout << "EatCheese -> walkingWithBomb" << std::endl;
	t_a->setCurrent(new WalkWithBombState());
	delete this;
}
void EatCheeseState::walking(AnimatedSpriteComponent* t_a)
{
	std::cout << "EatCheese -> walking" << std::endl;
	t_a->setCurrent(new WalkingState());
	delete this;
}

