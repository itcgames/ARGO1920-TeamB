#pragma once

#include "State.h"

class InteractState : public State
{
public:
	InteractState();
	~InteractState();
	void walking(AnimatedSpriteComponent* t_a);

	void attack(AnimatedSpriteComponent* t_a);

	void idle(AnimatedSpriteComponent* t_a);
};

