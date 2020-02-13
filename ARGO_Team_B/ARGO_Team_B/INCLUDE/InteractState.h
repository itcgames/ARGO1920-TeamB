#ifndef INTERACT_STATE
#define INTERACT_STATE

#include "State.h"
class AnimatedSpriteComponent;
class InteractState : public State
{
public:
	InteractState() {};
	~InteractState() {};
	void walking(AnimatedSpriteComponent* t_a)
	{
		std::cout << "Interact -> Walking" << std::endl;
		t_a->setCurrent(new WalkingState());
		delete this;
	}

	void attack(AnimatedSpriteComponent* t_a) {
		std::cout << "Interact -> attack" << std::endl;
		t_a->setCurrent(new AttackState());
		delete this;
	}

	void idle(AnimatedSpriteComponent* t_a) {
		std::cout << "Interact -> Idle " << std::endl;
		t_a->setCurrent(new IdleState());
		delete this;
	}
};

#endif // !INTERACT_STATE
