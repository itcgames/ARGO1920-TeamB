#define CUTE_C2_IMPLEMENTATION

#include "CollisionComponent.h"

CollisionComponent::CollisionComponent(Entity& t_gameObject, float diameter, int width, int height) :
	m_width(width),
	m_height(height),
	m_entity(t_gameObject)
{
	PositionComponent* entityPos = static_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));
	m_circlecollider.p = { entityPos->getPositionX() - width / 2, entityPos->getPositionY() - height / 2};
	m_circlecollider.r = diameter / 2;

}

CollisionComponent::CollisionComponent(Entity& t_gameObject, int width, int height):
	m_width(width),
	m_height(height),
	m_entity(t_gameObject)
{
	PositionComponent* entityPos = static_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));
	m_recCollider.min = { entityPos->getPositionX(), entityPos->getPositionY()};
	m_recCollider.max = { entityPos->getPositionX() + width, entityPos->getPositionY() + height};
}

CollisionComponent::CollisionComponent(Entity& t_gameObject, int width, int height, int count):
	m_width(width),
	m_height(height),
	m_entity(t_gameObject)
{
	PositionComponent* entityPos = static_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));
	m_polyCollider.count = count;
	m_polyCollider.verts[0] = { entityPos->getPositionX(), entityPos->getPositionY()};
	m_polyCollider.verts[1] = { entityPos->getPositionX(), entityPos->getPositionY() + m_height };
	m_polyCollider.verts[2] = { entityPos->getPositionX() + m_width, entityPos->getPositionY() + m_height };
	m_polyCollider.verts[3] = { entityPos->getPositionX() + m_width, entityPos->getPositionY()};
	c2MakePoly(&m_polyCollider);
}

CollisionComponent::~CollisionComponent()
{
}

void CollisionComponent::reset()
{
	PositionComponent* entityPos = static_cast<PositionComponent*>(m_entity.getComponent(Types::Position));
	m_circlecollider.p = { entityPos->getPositionX() - m_width / 2, entityPos->getPositionY() - m_height / 2 };
}

void CollisionComponent::updateCollider(Entity& t_entity)
{
	PositionComponent* entityPos = static_cast<PositionComponent*>(t_entity.getComponent(Types::Position));
	m_circlecollider.p = c2v{ entityPos->getPositionX(), entityPos->getPositionY()};

	m_recCollider.min = { entityPos->getPositionX(), entityPos->getPositionY() };
	m_recCollider.max = { entityPos->getPositionX() + m_width, entityPos->getPositionY() + m_height };

}

void CollisionComponent::updateCollider(Entity& t_entity, double angle)
{
	PositionComponent* entityPos = static_cast<PositionComponent*>(t_entity.getComponent(Types::Position));

	float originX = entityPos->getPositionX() + m_width / 2;
	float originY = entityPos->getPositionY() + m_height / 2;

	std::cout << "origin x: " << originX << "origin y: " << originY << std::endl;

	float CosWithAngle = cos(angle / (180 / 3.14));
	float SinWithAngle = sin(angle / (180 / 3.14));

	m_polyCollider.verts[0] = { originX + (CosWithAngle * (-m_width / 2) - SinWithAngle * (-m_height / 2)), originY + (SinWithAngle * (-m_width / 2) + CosWithAngle * (-m_height / 2))};
	//std::cout << "Position1 x: " << m_polyCollider.verts[0].x << "Position1 y: " << m_polyCollider.verts[0].y << std::endl;
	m_polyCollider.verts[1] = { originX + (CosWithAngle * (-m_width / 2) - SinWithAngle * (m_height / 2)), originY + (SinWithAngle * (-m_width / 2) + CosWithAngle * (m_height / 2))};
	//std::cout << "Position2 x: " << m_polyCollider.verts[1].x << "Position2 y: " << m_polyCollider.verts[1].y << std::endl;
	m_polyCollider.verts[2] = { originX + (CosWithAngle * (m_width / 2) - SinWithAngle * (m_height / 2)), originY + (SinWithAngle * (m_width / 2) + CosWithAngle * (m_height / 2))};
	//std::cout << "Position3 x: " << m_polyCollider.verts[2].x << "Position3 y: " << m_polyCollider.verts[2].y << std::endl;
	m_polyCollider.verts[3] = { originX + (CosWithAngle * (m_width / 2) - SinWithAngle * (-m_height / 2)), originY + (SinWithAngle * (m_width / 2) + CosWithAngle * (-m_height / 2))};
	//std::cout << "Position4 x: " << m_polyCollider.verts[3].x << "Position4 y: " << m_polyCollider.verts[3].y << std::endl;
	c2MakePoly(&m_polyCollider);

}

void CollisionComponent::setCircleRadius(float radius)
{
	m_circlecollider.r = radius;
}

