#ifndef STATE_H
#define STATE_H

#include <iostream>

class AnimatedSpriteComponent;
class State
{
public:
	virtual void idle(AnimatedSpriteComponent* t_a)
	{
		std::cout << "Idle State" << std::endl;
	}
	
	virtual void walking(AnimatedSpriteComponent* t_a)
	{
		std::cout << "walking State" << std::endl;
	}

	virtual void stunned(AnimatedSpriteComponent* t_a)
	{
		std::cout << "stunned State" << std::endl;
	}

	virtual void attack(AnimatedSpriteComponent* t_a)
	{
		std::cout << "attack State" << std::endl;
	}

	virtual void interact(AnimatedSpriteComponent* t_a)
	{
		std::cout << "interact State" << std::endl;
	}
};

#include "AnimatedSpriteComponent.h"


//
///// <summary>
///// ------------------------ Idle State -----------------------------
///// </summary>
//class IdleState : public State
//{
//public:
//	IdleState() {};
//	~IdleState() {};
//
//	void walking(AnimatedSpriteComponent * t_a)
//	{
//		std::cout << "Idle -> Walking" << std::endl;
//		t_a->setCurrent(new WalkingState());
//		delete this;
//	};
//
//	void stunned(AnimatedSpriteComponent* t_a)
//	{
//		std::cout << "Idle -> stunned" << std::endl;
//		t_a->setCurrent(new StunnedState());
//		delete this;
//	};
//
//	void attack(AnimatedSpriteComponent* t_a) {
//		std::cout << "Idle -> attack" << std::endl;
//		t_a->setCurrent(new AttackState());
//		delete this;
//	};
//
//	void interact(AnimatedSpriteComponent* t_a) {
//		std::cout << "Idle -> Interact" << std::endl;
//		t_a->setCurrent(new InteractState());
//		delete this;
//	};
//
//};

/// <summary>
/// ------------------------ Stunned State -----------------------------
/// </summary>


/// <summary>
/// ------------------------ Walking State -----------------------------
/// </summary>


/// <summary>
/// ------------------------ Attack State -----------------------------
/// </summary>


/// <summary>
/// ------------------------ interact State -----------------------------
/// </summary>


#endif // !STATE_H

