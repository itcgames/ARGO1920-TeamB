#pragma once
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
private:
	float m_currentX;
	float m_currentY;
};