#include "PositionComponent.h"

PositionComponent::PositionComponent(float t_x, float t_y) :
	m_currentX(t_x),
	m_currentY(t_y),
	m_velocityX(0),
	m_velocityY(0)
{
}

PositionComponent::~PositionComponent()
{
}

float PositionComponent::getPositionX()
{
	return m_currentX;
}
float PositionComponent::getPositionY()
{
	return m_currentY;
}

void PositionComponent::setPosition(float t_x, float t_y)
{
	m_currentX = t_x;
	m_currentY = t_y;
}

void PositionComponent::setVelo(float t_x, float t_y)
{
	m_velocityX = t_x;
	m_velocityY = t_y;
}

void PositionComponent::moveUp()
{
	if (m_velocityY > -MAX_VELO) {
		m_velocityY -= INC_VELO;
	}
}

void PositionComponent::moveDown()
{
		m_velocityY += INC_VELO;
	if (m_velocityY < MAX_VELO) {
	}
}

void PositionComponent::moveLeft()
{
	if (m_velocityX > -MAX_VELO) {
		m_velocityX -= INC_VELO;
	}
}

void PositionComponent::moveRight()
{
	if (m_velocityX < MAX_VELO) {
		m_velocityX += INC_VELO;
	}
}
