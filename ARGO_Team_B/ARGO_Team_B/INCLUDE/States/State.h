#pragma once
#include <iostream>
#include "Enums.h"
#include "AnimatedSpriteComponent.h"

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
	virtual void walkWithBomb(AnimatedSpriteComponent* t_a)
	{
		std::cout << "walkWithBomb State" << std::endl;
	}
	virtual void eatCheese(AnimatedSpriteComponent* t_a)
	{
		std::cout << "eatCheese State" << std::endl;
	}
	virtual States getType() { return m_type; };

	States m_type = States::Idle;
};
