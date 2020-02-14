#pragma once

#include "State.h"


class WalkingState : public State
{
public:
	WalkingState();
	~WalkingState();

	void idle(AnimatedSpriteComponent* t_a);
	void stunned(AnimatedSpriteComponent* t_a);
	void attack(AnimatedSpriteComponent* t_a);

};
