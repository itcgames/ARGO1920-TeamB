#define CUTE_C2_IMPLEMENTATION

#include "CollisionComponent.h"

CollisionComponent::CollisionComponent(Entity& t_gameObject, float diameter)
{
	PositionComponent* entityPos = static_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));

	float rotatedAngleX = (entityPos->getPositionX() * cos(entityPos->getAngle())) - (entityPos->getPositionY() * sin(entityPos->getAngle()));
	float rotatedAngleY = (entityPos->getPositionX() * sin(entityPos->getAngle())) + (entityPos->getPositionY() * cos(entityPos->getAngle()));

	m_circlecollider.p = { entityPos->getPositionX(), entityPos->getPositionY() };
	m_circlecollider.r = diameter / 2;
}

CollisionComponent::CollisionComponent(Entity& t_gameObject, int width, int height):
	m_width(width),
	m_height(height)
{
	PositionComponent* entityPos = static_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));

	float rotatedAngleX = (entityPos->getPositionX() * cos(entityPos->getAngle())) - (entityPos->getPositionY() * sin(entityPos->getAngle()));
	float rotatedAngleY = (entityPos->getPositionX() * sin(entityPos->getAngle())) + (entityPos->getPositionY() * cos(entityPos->getAngle()));

	float rotatedAngleXEnd = (entityPos->getPositionX() + width * cos(entityPos->getAngle())) - (entityPos->getPositionY() + height * sin(entityPos->getAngle()));
	float rotatedAngleYEnd = (entityPos->getPositionX() + width * sin(entityPos->getAngle())) + (entityPos->getPositionY() + height * cos(entityPos->getAngle()));

	m_recCollider.min = { rotatedAngleX, rotatedAngleY};
	m_recCollider.max = { rotatedAngleXEnd, rotatedAngleYEnd};
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

CollisionComponent::CollisionComponent(Entity& t_gameObject, int t_width, int t_height, float radius):
	m_width(t_width),
	m_height(t_height)
{
	PositionComponent* entityPos = static_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));

	m_capsuleCollider.a.x = ((entityPos->getPositionX() + m_width/2) * cos(entityPos->getAngle() * (3.14 / 180)));
	m_capsuleCollider.a.y = (entityPos->getPositionY() * sin(entityPos->getAngle() * (3.14 / 180)));

	m_capsuleCollider.b.x = ((entityPos->getPositionX() + m_width / 2) * cos(entityPos->getAngle() * (3.14 / 180)));
	m_capsuleCollider.b.y = ((entityPos->getPositionY() + m_height) * sin(entityPos->getAngle() * (3.14 / 180)));
	m_capsuleCollider.r = radius;					 
}

CollisionComponent::~CollisionComponent()
{
}

void CollisionComponent::updateCollider(Entity& t_entity)
{
	PositionComponent* entityPos = static_cast<PositionComponent*>(t_entity.getComponent(Types::Position));
	m_circlecollider.p = c2v{ entityPos->getPositionX(), entityPos->getPositionY() };


	/// <summary>
	/// Update Capsule
	/// </summary>
	m_capsuleCollider.a.x = (entityPos->getPositionX() * cos(entityPos->getAngle() * 3.14/180)) - (entityPos->getPositionY() + m_capsuleCollider.r * sin(entityPos->getAngle() * 3.14 / 180));
	m_capsuleCollider.a.y = entityPos->getPositionX() * sin(entityPos->getAngle() * 3.14 / 180) + entityPos->getPositionY() + m_capsuleCollider.r * cos(entityPos->getAngle() * 3.14 / 180);

	m_capsuleCollider.b.x = (entityPos->getPositionX() + m_width * cos(entityPos->getAngle())) + ((entityPos->getPositionY() + m_capsuleCollider.r) * sin(entityPos->getAngle()));
	m_capsuleCollider.b.y = (entityPos->getPositionX() + m_width * sin(entityPos->getAngle())) + ((entityPos->getPositionY() + m_capsuleCollider.r) * cos(entityPos->getAngle()));


	/// <summary>
	/// Updating Rectangle
	/// </summary>
 	float rotatedAngleX = (entityPos->getPositionX() * cos(entityPos->getAngle() * (3.14 / 180))) - (entityPos->getPositionY() * sin(entityPos->getAngle() * (3.14 / 180)));
	float rotatedAngleY = (entityPos->getPositionX() * sin(entityPos->getAngle() * (3.14 / 180))) + (entityPos->getPositionY() * cos(entityPos->getAngle() * (3.14 / 180)));

	float rotatedAngleXEnd = ((entityPos->getPositionX() + m_width) * cos(entityPos->getAngle() * (3.14 / 180))) - ((entityPos->getPositionY() + m_height) * sin(entityPos->getAngle() * (3.14 / 180)));
  	float rotatedAngleYEnd = ((entityPos->getPositionX() + m_width) * sin(entityPos->getAngle() * (3.14 / 180))) + ((entityPos->getPositionY() + m_height) * cos(entityPos->getAngle() * (3.14 / 180)));


	m_recCollider.min = { rotatedAngleX, rotatedAngleY };
	m_recCollider.max = { rotatedAngleXEnd, rotatedAngleYEnd };

	//m_recCollider.min = { entityPos->getPositionX(), entityPos->getPositionY() };
	//m_recCollider.max = { entityPos->getPositionX() + m_width, entityPos->getPositionY() + m_height };

	//m_polyCollider.verts[0] = { entityPos->getPositionX() + m_width / 2, entityPos->getPositionY() + m_height / 2 };
	//m_polyCollider.verts[1] = { entityPos->getPositionX(), entityPos->getPositionY() + m_height };
	//m_polyCollider.verts[2] = { entityPos->getPositionX() + m_width, entityPos->getPositionY() + m_height };
	//c2MakePoly(&m_polyCollider);
}

