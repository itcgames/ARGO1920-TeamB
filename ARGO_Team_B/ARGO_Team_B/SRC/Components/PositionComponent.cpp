#include "PositionComponent.h"

PositionComponent::PositionComponent(float t_x, float t_y) :
	m_currentX(t_x),
	m_currentY(t_y),
	m_velocityX(0),
	m_velocityY(0),
	m_lastX(m_currentX),
	m_lastY(m_currentY),
	m_startX(t_x),
	m_startY(t_y),
	m_acceleration(120)
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
	m_velocityX = -m_velocityX * 0.5;
	m_velocityY = -m_velocityY * 0.5;
}

void PositionComponent::setVelo(float t_x, float t_y)
{
	m_velocityX = t_x;
	m_velocityY = t_y;
}
void PositionComponent::setPreviousePos() {
	m_previousX = m_currentX;
	m_previousY = m_currentY;

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
	m_currentX = m_previousX;
	m_currentY = m_previousY;
}

void PositionComponent::movementUpdate(float dt) {
	m_lastX = m_currentX;
	m_lastY = m_currentY;

	m_currentY = m_currentY + m_velocityY * dt;
	m_currentX = m_currentX + m_velocityX * dt;

	if (m_velocityY <= 0.01f && m_velocityY >= -0.01f) {
		m_velocityY = 0;
	}
	if (m_velocityX <= 0.01f && m_velocityX >= -0.01f) {
		m_velocityX = 0;
	}
}

void PositionComponent::moveUp()
{
	m_lastY = m_currentY;

	/*m_acceleration = rand() % MAX_VELO;
	m_currentY -= m_acceleration;*/

	m_velocityY = m_velocityY - (m_acceleration * 1.0f / 6.0f);
	if (m_velocityY < -m_acceleration) {
		m_velocityY = -m_acceleration;
	}

}

void PositionComponent::moveDown()
{
	m_lastY = m_currentY;
	/*m_acceleration = rand() % MAX_VELO;
	m_currentY += m_acceleration;*/

	m_velocityY = m_velocityY + (m_acceleration * 1.0f / 6.0f);
	if (m_velocityY > m_acceleration) {
		m_velocityY = m_acceleration;
	}
}

void PositionComponent::moveLeft()
{
	m_lastX = m_currentX;
	/*m_acceleration = rand() % MAX_VELO;
	m_currentX -= m_acceleration;*/

	m_velocityX = m_velocityX - (m_acceleration * 1.0f / 60.0f);
	if (m_velocityX < -m_acceleration) {
		m_velocityX = -m_acceleration;
	}
}

void PositionComponent::moveRight()
{
	m_lastX = m_currentX;
	/*m_acceleration = rand() % MAX_VELO;
	m_currentX += m_acceleration;*/

	m_velocityX = m_velocityX + (m_acceleration * 1.0f / 60.0f);
	if (m_velocityX > m_acceleration) {
		m_velocityX = m_acceleration;
	}
}

void PositionComponent::slowDownX()
{
	m_velocityX = m_velocityX * 0.9;
}

void PositionComponent::slowDownY()
{
	m_velocityY = m_velocityY * 0.9;
}

