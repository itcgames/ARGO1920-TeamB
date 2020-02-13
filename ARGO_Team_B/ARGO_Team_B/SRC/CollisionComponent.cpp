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


	float offsetX  = entityPos->getPositionX() + m_width /2;
	float offsetY = entityPos->getPositionY();
	float offsetX2 = entityPos->getPositionX()- m_width / 2;

	/// <summary>
	/// Update Capsule
	/// </summary>

	m_capsuleCollider.a.x = entityPos->getPositionX();
	m_capsuleCollider.a.y = entityPos->getPositionY();
	m_capsuleCollider.b.x = entityPos->getPositionX();
	m_capsuleCollider.b.y = entityPos->getPositionY();
	
	/*float x_rotated = ((x - x_origin) * cos(angle)) - ((y_origin - y) * sin(angle)) + x_origin;
	float y_rotated = ((y_origin - y) * cos(angle)) - ((x - x_origin) * sin(angle)) + y_origin;*/

	float aX = ((m_capsuleCollider.a.x - offsetX) * cos(entityPos->getAngle() * (3.14 / 180)) - ((offsetY - m_capsuleCollider.a.y ) * sin(entityPos->getAngle() * 3.14 / 180)));
	float aY = ((offsetY - m_capsuleCollider.a.y) * cos(entityPos->getAngle() * (3.14 / 180)) - ((m_capsuleCollider.a.x - offsetX) * sin(entityPos->getAngle() * 3.14 / 180)));

	float bX = ((m_capsuleCollider.b.x - offsetX) * cos(entityPos->getAngle() * (3.14 / 180)) - ((offsetY - m_capsuleCollider.b.y) * sin(entityPos->getAngle() * 3.14 / 180)));
	float bY = ((offsetY - m_capsuleCollider.b.y) * cos(entityPos->getAngle() * (3.14 / 180)) - ((m_capsuleCollider.b.x - offsetX) * sin(entityPos->getAngle() * 3.14 / 180)));

	//m_capsuleCollider.a.x = (m_capsuleCollider.a.x * cos(entityPos->getAngle() * (3.14 / 180)) - (m_capsuleCollider.a.y * sin(entityPos->getAngle() * 3.14 / 180)));
	//m_capsuleCollider.a.y = (m_capsuleCollider.a.x * sin(entityPos->getAngle() * (3.14 / 180)) + (m_capsuleCollider.a.y * cos(entityPos->getAngle() * 3.14 / 180)));
	/*
	m_capsuleCollider.b.x = (m_capsuleCollider.b.x * cos(entityPos->getAngle() * 3.14 / 180)) - (m_capsuleCollider.b.y * sin(entityPos->getAngle() * 3.14 / 180));
	m_capsuleCollider.b.y = (m_capsuleCollider.b.x * sin(entityPos->getAngle() * 3.14 / 180)) + (m_capsuleCollider.b.y * cos(entityPos->getAngle() * 3.14 / 180)); */

	m_capsuleCollider.a.x = aX + offsetX;
	m_capsuleCollider.a.y = aY + offsetY;
	m_capsuleCollider.b.x = bX + offsetX2;
	m_capsuleCollider.b.y = bY + offsetY;

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

