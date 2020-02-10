#ifndef COLLISION_COMPONENT
#define COLLISION_COMPONENT

#include "Component.h"
#include "PositionComponent.h"
#include "Entity.h"
#include <iostream>
#include <cute_c2.h>
#include <vector>

#include "Globals.h"

class CollisionComponent : public Component
{
public:
	CollisionComponent();
	void updateCollider(Entity& t_entity);
	~CollisionComponent();
	c2Circle getCollider() { return m_collider; }
private:
	c2Circle m_collider;
};
#endif // !COLLISION_COMPONENT