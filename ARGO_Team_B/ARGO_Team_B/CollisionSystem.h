#ifndef COLLISION_SYSTEM
#define COLLISION_SYSTEM

#include "System.h"
#include "CollisionComponent.h"

class CollisionSystem : public System
{
public:
	CollisionSystem();
	~CollisionSystem();
	void updateComponent(Component* component) override;
};
#endif // !COLLISION_SYSTEM