#pragma once
#include <iostream>

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
};

#include "AnimatedSpriteComponent.h"
