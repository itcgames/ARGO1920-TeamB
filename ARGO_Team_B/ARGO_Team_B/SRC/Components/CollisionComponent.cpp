#define CUTE_C2_IMPLEMENTATION

#include "CollisionComponent.h"

CollisionComponent::CollisionComponent(Entity& t_gameObject, float diameter, int width, int height) :
	m_width(width),
	m_height(height)
{
	PositionComponent* entityPos = static_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));
	m_circlecollider.p = { entityPos->getPositionX() + width / 2, entityPos->getPositionY() + height / 2};
	m_circlecollider.r = diameter / 2;

}

CollisionComponent::CollisionComponent(Entity& t_gameObject, int width, int height):
	m_width(width),
	m_height(height)
{
	PositionComponent* entityPos = static_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));
	m_recCollider.min = { entityPos->getPositionX(), entityPos->getPositionY()};
	m_recCollider.max = { entityPos->getPositionX() + width, entityPos->getPositionY() + height};
}

CollisionComponent::CollisionComponent(Entity& t_gameObject, int width, int height, int count):
	m_width(width),
	m_height(height)
{
	PositionComponent* entityPos = static_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));
	m_polyCollider.count = count;
	m_polyCollider.verts[0] = { entityPos->getPositionX() + width / 2, entityPos->getPositionY() + height / 2 };
	m_polyCollider.verts[1] = { entityPos->getPositionX(), entityPos->getPositionY() + height};
	m_polyCollider.verts[2] = { entityPos->getPositionX() + width, entityPos->getPositionY() + height};
	c2MakePoly(&m_polyCollider);
}

CollisionComponent::~CollisionComponent()
{
}

void CollisionComponent::updateCollider(Entity& t_entity)
{
	PositionComponent* entityPos = static_cast<PositionComponent*>(t_entity.getComponent(Types::Position));
	m_circlecollider.p = c2v{ entityPos->getPositionX() + m_width / 2, entityPos->getPositionY() + m_height / 2 };

	m_recCollider.min = { entityPos->getPositionX(), entityPos->getPositionY() };
	m_recCollider.max = { entityPos->getPositionX() + m_width, entityPos->getPositionY() + m_height };
	
	m_polyCollider.verts[0] = { entityPos->getPositionX() + m_width / 2, entityPos->getPositionY() + m_height / 2 };
	m_polyCollider.verts[1] = { entityPos->getPositionX(), entityPos->getPositionY() + m_height };
	m_polyCollider.verts[2] = { entityPos->getPositionX() + m_width, entityPos->getPositionY() + m_height };
	c2MakePoly(&m_polyCollider);
}

void CollisionComponent::setCircleRadius(float radius)
{
	m_circlecollider.r = radius;
}

