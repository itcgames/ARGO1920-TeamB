#ifndef IDLE_STATE_H

#include "state.h"

class IdleState : public State
{
public:
	IdleState() {};
	~IdleState() {};

	void walking(AnimatedSpriteComponent* t_a)
	{
		std::cout << "Idle -> Walking" << std::endl;
		t_a->setCurrent(new WalkingState());
		delete this;
	};

	void stunned(AnimatedSpriteComponent* t_a)
	{
		std::cout << "Idle -> stunned" << std::endl;
		t_a->setCurrent(new StunnedState());
		delete this;
	};
	void attack(AnimatedSpriteComponent* t_a) {
		std::cout << "Idle -> attack" << std::endl;
		t_a->setCurrent(new AttackState());
		delete this;
	};

	void interact(AnimatedSpriteComponent* t_a) {
		std::cout << "Idle -> interact" << std::endl;
		t_a->setCurrent(new InteractState());
		delete this;
	};


};

#endif // !IDLE_STATE_H
