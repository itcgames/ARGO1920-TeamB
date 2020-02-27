#ifndef COLLISION_COMPONENT
#define COLLISION_COMPONENT

#include "Component.h"
#include "PositionComponent.h"
#include "Entity.h"
#include <iostream>
#include <cute_c2.h>
#include <vector>
#include <math.h>

#include "Enums.h"
#include "SDL.h"

class CollisionComponent : public Component
{
public:
	CollisionComponent(Entity& t_gameObject, float diameter, int width, int height);
	CollisionComponent(Entity& t_gameObject, int width, int height);
	CollisionComponent(Entity& t_gameObject, int width, int height, int count);

	void updateCollider(Entity& t_entity);
	void updateCollider(Entity& t_entity, double angle);

	void setCircleRadius(float radiuss);

	~CollisionComponent();

	c2Circle getCircleCollider() { return m_circlecollider; }
	c2AABB getAABBCollider() { return m_recCollider; }
	c2Poly getPolyCollider() { return m_polyCollider; }

	void reset();
private:
	Entity& m_entity;
	c2Circle m_circlecollider;
	c2AABB m_recCollider;
	c2Poly m_polyCollider;


	int m_width, m_height;
};
#endif // !COLLISION_COMPONENT