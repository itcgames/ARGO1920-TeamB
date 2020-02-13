#ifndef ATTACK_STATE
#define ATTACK_STATE

#include "State.h"
class AnimatedSpriteComponent;
class AttackState : public State
{
public:
	AttackState() {};
	~AttackState() {};

	void stunned(AnimatedSpriteComponent* t_a)
	{
		std::cout << "Attack -> stunned" << std::endl;
		t_a->setCurrent(new StunnedState());
		delete this;
	}

	void idle(AnimatedSpriteComponent* t_a) {
		std::cout << "attack -> Idle" << std::endl;
		t_a->setCurrent(new IdleState());
		delete this;
	}
};

#endif // !ATTACK_STATE
