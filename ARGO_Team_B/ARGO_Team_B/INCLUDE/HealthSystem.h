#pragma once
#include "System.h"
#include "HealthComponent.h"

class HealthSystem : public System
{
public:
	HealthSystem();
	~HealthSystem();
	void updateComponent(Component* component) override;
};