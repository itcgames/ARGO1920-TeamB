#define CUTE_C2_IMPLEMENTATION

#include "CollisionComponent.h"

CollisionComponent::CollisionComponent()
{
	m_collider.p = { -100, -100 };
	m_collider.r = RAT_H / 2;
}

CollisionComponent::~CollisionComponent()
{
}

void CollisionComponent::updateCollider(Entity& t_entity)
{
	PositionComponent* entityPos = static_cast<PositionComponent*>(t_entity.getComponent(Types::Position));
	m_collider.p = c2v{ entityPos->getPositionX(), entityPos->getPositionY() };
}