#include "CollisionSystem.h"

CollisionSystem::CollisionSystem()
{
}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::updateComponent(Component* component)
{
	Collision* hc = dynamic_cast<HealthComponent*>(component);
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
