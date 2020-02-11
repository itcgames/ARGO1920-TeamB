#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "Component.h"
class PositionComponent : public Component
{
public:
	PositionComponent(float t_x, float t_y);
	~PositionComponent();
	float getPositionX();
	float getPositionY();
	void setPosition(float t_x, float t_y);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	float getLastX() { return m_lastX; }
	float getLastY() { return m_lastY; }
private:
	float m_currentX;
	float m_currentY;

	float m_lastX;
	float m_lastY;
};
#endif // !POS
