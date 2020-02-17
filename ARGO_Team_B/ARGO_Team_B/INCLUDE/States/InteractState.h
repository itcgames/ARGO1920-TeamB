#pragma once

#include "State.h"

class InteractState : public State
{
public:
	InteractState();
	~InteractState();
	void walking(AnimatedSpriteComponent* t_a) override;

	void attack(AnimatedSpriteComponent* t_a) override;

	void idle(AnimatedSpriteComponent* t_a) override;
};

