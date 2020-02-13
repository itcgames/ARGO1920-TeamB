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
	CollisionComponent(Entity& t_gameObject, float diameter);
	CollisionComponent(Entity& t_gameObject, int width, int height);
	CollisionComponent(Entity& t_gameObject, int width, int height, int count);
	CollisionComponent(Entity& t_gameObject, int t_width, int t_height, float radius);

	void updateCollider(Entity& t_entity);
	~CollisionComponent();

	c2Circle getCircleCollider() { return m_circlecollider; }
	c2AABB getAABBCollider() { return m_recCollider; }
	c2Poly getPolyCollider() { return m_polyCollider; }
	c2Capsule getCapsuleCollider() { return m_capsuleCollider; };
private:
	c2Capsule m_capsuleCollider;
	c2Circle m_circlecollider;
	c2AABB m_recCollider;
	c2Poly m_polyCollider;

	int m_width;
	int m_height;
};
#endif // !COLLISION_COMPONENT