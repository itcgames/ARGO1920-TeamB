#include "PositionComponent.h"

PositionComponent::PositionComponent(float t_x, float t_y) :
	m_currentX(t_x),
	m_currentY(t_y)
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

void PositionComponent::setPreviousePos() {
	m_previouseX = m_currentX;
	m_previouseY = m_currentY;
}

void PositionComponent::backToPreviousePos() {
	m_currentX = m_previouseX;
	m_currentY = m_previouseY ;
}

void PositionComponent::moveUp()
{
	m_currentY-=3;
}

void PositionComponent::moveDown()
{
	m_currentY += 3;
}

void PositionComponent::moveLeft()
{
	m_currentX -= 3;
}

void PositionComponent::moveRight()
{
	m_currentX += 3;
}
