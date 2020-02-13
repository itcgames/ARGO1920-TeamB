#ifndef STUNNED_STATE
#define STUNNED_STATE

#include "State.h"
class AnimatedSpriteComponent;
class StunnedState : public State
{
public:
	StunnedState() {};
	~StunnedState() {};

	void walking(AnimatedSpriteComponent* t_a)
	{
		std::cout << "Stunned -> Walking" << std::endl;
		t_a->setCurrent(new WalkingState());
		delete this;
	}

	void idle(AnimatedSpriteComponent* t_a) {
		std::cout << "Stunned -> idle" << std::endl;
		t_a->setCurrent(new IdleState());
		delete this;
	}
};

#endif // !STUNNED_STATE
