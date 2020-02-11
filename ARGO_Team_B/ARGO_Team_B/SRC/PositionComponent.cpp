#include "PositionComponent.h"

PositionComponent::PositionComponent(float t_x, float t_y) :
	m_currentX(t_x),
	m_currentY(t_y),
	m_lastX(m_currentX),
	m_lastY(m_currentY)
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

void PositionComponent::moveUp()
{

	m_lastY = m_currentY;
	m_currentY-=3;
}

void PositionComponent::moveDown()
{
	m_lastY= m_currentY;
	m_currentY += 3;
}

void PositionComponent::moveLeft()
{
	m_lastX = m_currentX;
	m_currentX -= 3;
}

void PositionComponent::moveRight()
{
	m_lastX = m_currentX;
	m_currentX += 3;
}
