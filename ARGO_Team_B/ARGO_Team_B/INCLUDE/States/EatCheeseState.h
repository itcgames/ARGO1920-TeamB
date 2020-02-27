#pragma once

#include "State.h"


class EatCheeseState : public State
{
public:
	EatCheeseState();
	~EatCheeseState();

	void idle(AnimatedSpriteComponent* t_a)override;
	void walkWithBomb(AnimatedSpriteComponent* t_a)override;
	void walking(AnimatedSpriteComponent* t_a)override;


};
