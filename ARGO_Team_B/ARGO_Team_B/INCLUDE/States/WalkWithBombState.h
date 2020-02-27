#pragma once

#include "State.h"


class WalkWithBombState : public State
{
public:
	WalkWithBombState();
	~WalkWithBombState();

	void idle(AnimatedSpriteComponent* t_a)override;
	void stunned(AnimatedSpriteComponent* t_a)override;
	void attack(AnimatedSpriteComponent* t_a)override;
	void walking(AnimatedSpriteComponent* t_a)override;
};
