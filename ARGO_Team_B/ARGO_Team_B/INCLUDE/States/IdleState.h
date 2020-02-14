#pragma once
#include "State.h"

#include "StunnedState.h"
#include "WalkingState.h"
#include "AttackState.h"
#include "InteractState.h"

class IdleState : public State
{
public:
	IdleState() {}
	~IdleState() {}

	void walking(AnimatedSpriteComponent* t_a)
	{
		std::cout << "Idle -> Walking" << std::endl;
		t_a->setCurrent(new WalkingState());
		delete this;
	}

	void stunned(AnimatedSpriteComponent* t_a)
	{
		std::cout << "Idle -> stunned" << std::endl;
		t_a->setCurrent(new StunnedState());
		delete this;
	}

	void attack(AnimatedSpriteComponent* t_a) {
		std::cout << "Idle -> attack" << std::endl;
		t_a->setCurrent(new AttackState());
		delete this;
	}

	void interact(AnimatedSpriteComponent* t_a) {
		std::cout << "Idle -> interact" << std::endl;
		t_a->setCurrent(new InteractState());
		delete this;
	}
};

