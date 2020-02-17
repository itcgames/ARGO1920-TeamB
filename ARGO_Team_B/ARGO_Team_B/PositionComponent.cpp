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
	if (m_velocityY > -MAX_VELO) {
		m_velocityY -= INC_VELO;
	}

	m_lastY = m_currentY;
	m_acceleration = rand() % 4;
	m_currentY -= m_acceleration;
}

void PositionComponent::moveDown()
{
	m_velocityY += INC_VELO;
	if (m_velocityY < MAX_VELO) {
	}
	m_lastY = m_currentY;
	m_acceleration = rand() % 4;
	m_currentY += m_acceleration;
}

void PositionComponent::moveLeft()
{
	if (m_velocityX > -MAX_VELO) {
		m_velocityX -= INC_VELO;
	}
	m_lastX = m_currentX;
	m_acceleration = rand() % 4;
	m_currentX -= m_acceleration;
}

void PositionComponent::moveRight()
{
	if (m_velocityX < MAX_VELO) {
		m_velocityX += INC_VELO;
	}
	m_lastX = m_currentX;
	m_acceleration = rand() % 4;
	m_currentX += m_acceleration;
}

