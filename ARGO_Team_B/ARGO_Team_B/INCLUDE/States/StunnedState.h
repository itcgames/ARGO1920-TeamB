#pragma once
#include "State.h"

class StunnedState : public State
{
public:
	StunnedState();
	~StunnedState();

	void walking(AnimatedSpriteComponent* t_a);
	void idle(AnimatedSpriteComponent* t_a);
};