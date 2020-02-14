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

	void backToPreviousePos();
	void setPreviousePos();

	float getLastX() { return m_lastX; }
	float getLastY() { return m_lastY; }

	void backToStart();
private:
	float m_currentX;
	float m_currentY;

	float m_startX;
	float m_startY;

	float m_previouseX;
	float m_previouseY;

	float m_lastX;
	float m_lastY;
};
#endif // !POS
