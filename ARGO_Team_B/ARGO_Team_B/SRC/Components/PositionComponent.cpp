#include "PositionComponent.h"

PositionComponent::PositionComponent(float t_x, float t_y) :
	m_currentX(t_x),
	m_currentY(t_y),
	m_velocityX(0),
	m_velocityY(0),
	m_lastX(m_currentX),
	m_lastY(m_currentY),
	m_startX(t_x),
	m_startY(t_y)
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
void PositionComponent::setPreviousePos() {
	m_previouseX = m_currentX;
	m_previouseY = m_currentY;
}

void PositionComponent::setangle(double t_angle)
{
	m_angle = t_angle;
}

double PositionComponent::getangle()
{
	return m_angle;
}

void PositionComponent::backToStart()
{
	m_currentX = m_startX;
	m_currentY = m_startY;
}

void PositionComponent::backToPreviousePos() {
	m_currentX = m_previouseX;
	m_currentY = m_previouseY;
}

void PositionComponent::moveUp()
{
	m_lastY = m_currentY;
	m_acceleration = rand() % MAX_VELO;
	m_currentY -= m_acceleration;
}

void PositionComponent::moveDown()
{
	m_lastY = m_currentY;
	m_acceleration = rand() % MAX_VELO;
	m_currentY += m_acceleration;
}

void PositionComponent::moveLeft()
{
	m_lastX = m_currentX;
	m_acceleration = rand() % MAX_VELO;
	m_currentX -= m_acceleration;
}

void PositionComponent::moveRight()
{
	m_lastX = m_currentX;
	m_acceleration = rand() % MAX_VELO;
	m_currentX += m_acceleration;
}

