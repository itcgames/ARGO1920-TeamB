#include "PositionComponent.h"

PositionComponent::PositionComponent(int t_x, int t_y) :
	m_currentX(t_x),
	m_currentY(t_y)
{

}

PositionComponent::~PositionComponent()
{
}

int PositionComponent::getPositionX()
{
	return m_currentX;
}
int PositionComponent::getPositionY()
{
	return m_currentY;
}

void PositionComponent::setPosition(int t_x, int t_y)
{
	m_currentX = t_x;
	m_currentY = t_y;
}

void PositionComponent::moveUp()
{
	m_currentY-=1;
}

void PositionComponent::moveDown()
{
	m_currentY += 1;
}

void PositionComponent::moveLeft()
{
	m_currentX -= 1;
}

void PositionComponent::moveRight()
{
	m_currentX += 1;
}
