#ifndef HEALTH_SYSTEM
#define HEALTH_SYSTEM

#include "System.h"
#include "HealthComponent.h"

class HealthSystem : public System
{
public:
	HealthSystem();
	~HealthSystem();
	void updateComponent(Component* component) override;
};
#endif // !HEALTH_SYSTEM