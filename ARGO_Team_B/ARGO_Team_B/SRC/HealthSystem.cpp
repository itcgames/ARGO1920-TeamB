#include "HealthSystem.h"

HealthSystem::HealthSystem() {}

HealthSystem::~HealthSystem() {}

void HealthSystem::updateComponent(Component* component)
{
	HealthComponent* hc = dynamic_cast<HealthComponent*>(component);
	if (nullptr != hc)
	{
		int health = hc->getHealth();
		if (health <= 0)
		{
			hc->dead();
		}
	/*	hc->setHealth(health);*/

	}
}