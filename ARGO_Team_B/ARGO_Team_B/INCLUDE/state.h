#ifndef STATE_H
#define STATE_H

#include <iostream>
#include "AnimatedSpriteComponent.h"

class AnimatedSpriteComponent;

class State
{
public:
	virtual void idle(AnimatedSpriteComponent* t_a)
	{
		std::cout << "Idle State" << std::endl;
	};
	
	virtual void walking(AnimatedSpriteComponent* t_a)
	{
		std::cout << "walking State" << std::endl;
	};

	virtual void stunned(AnimatedSpriteComponent* t_a)
	{
		std::cout << "stunned State" << std::endl;
	};

	virtual void attack(AnimatedSpriteComponent* t_a)
	{
		std::cout << "attack State" << std::endl;
	};

	virtual void interact(AnimatedSpriteComponent* t_a)
	{
		std::cout << "interact State" << std::endl;
	};
};
//
///// <summary>
///// ------------------------ Idle State -----------------------------
///// </summary>

//
///// <summary>
///// ------------------------ Stunned State -----------------------------
///// </summary>
//
//class StunnedState : public State
//{
//public:
//	StunnedState() {};
//	~StunnedState() {};
//
//	void walking(AnimatedSpriteComponent* t_a)
//	{
//		std::cout << "Stunned -> Walking" << std::endl;
//		t_a->setCurrent(new WalkingState());
//		delete this;
//	};
//
//	void idle(AnimatedSpriteComponent* t_a) {
//		std::cout << "Stunned -> idle" << std::endl;
//		t_a->setCurrent(new IdleState());
//		delete this;
//	};
//
//};
//
///// <summary>
///// ------------------------ Walking State -----------------------------
///// </summary>
//
//class WalkingState : public State
//{
//public:
//	WalkingState() {};
//	~WalkingState() {};
//
//	void idle(AnimatedSpriteComponent* t_a)
//	{
//		std::cout << "Walking -> Idle" << std::endl;
//		t_a->setCurrent(new IdleState());
//		delete this;
//	};
//
//	void stunned(AnimatedSpriteComponent* t_a)
//	{
//		std::cout << "Walking -> stunned" << std::endl;
//		t_a->setCurrent(new StunnedState());
//		delete this;
//	};
//
//	void attack(AnimatedSpriteComponent* t_a) {
//		std::cout << "Walking -> attack" << std::endl;
//		t_a->setCurrent(new AttackState());
//		delete this;
//	};
//
//};
//
///// <summary>
///// ------------------------ Attack State -----------------------------
///// </summary>
//
//class AttackState: public State
//{
//public:
//	AttackState() {};
//	~AttackState() {};
//
//	void stunned(AnimatedSpriteComponent* t_a)
//	{
//		std::cout << "Attack -> stunned" << std::endl;
//		t_a->setCurrent(new StunnedState());
//		delete this;
//	};
//	
//	void idle(AnimatedSpriteComponent* t_a) {
//		std::cout << "attack -> Idle" << std::endl;
//		t_a->setCurrent(new IdleState());
//		delete this;
//	};
//
//};
//
///// <summary>
///// ------------------------ interact State -----------------------------
///// </summary>
//
//class InteractState : public State
//{
//public:
//	InteractState() {};
//	~InteractState() {};
//
//	void walking(AnimatedSpriteComponent* t_a)
//	{
//		std::cout << "Interact -> Walking" << std::endl;
//		t_a->setCurrent(new WalkingState());
//		delete this;
//	};
//
//	void attack(AnimatedSpriteComponent* t_a) {
//		std::cout << "Interact -> attack" << std::endl;
//		t_a->setCurrent(new AttackState());
//		delete this;
//	};
//
//	void idle(AnimatedSpriteComponent* t_a) {
//		std::cout << "Interact -> Idle " << std::endl;
//		t_a->setCurrent(new idleState());
//		delete this;
//	};
//
//
//};

#endif // !STATE_H

