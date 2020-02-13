#ifndef WALKING_STATE
#define WALKING_STATE

#include "State.h"
class AnimatedSpriteComponent;
class WalkingState : public State
{
public:
	WalkingState() {};
	~WalkingState() {};

	void idle(AnimatedSpriteComponent* t_a)
	{
		std::cout << "Walking -> Idle" << std::endl;
		t_a->setCurrent(new IdleState());
		delete this;
	}

	void stunned(AnimatedSpriteComponent* t_a)
	{
		std::cout << "Walking -> stunned" << std::endl;
		t_a->setCurrent(new StunnedState());
		delete this;
	}

	void attack(AnimatedSpriteComponent* t_a) {
		std::cout << "Walking -> attack" << std::endl;
		t_a->setCurrent(new AttackState());
		delete this;
	}

};

#endif // !WALKING_STATE
