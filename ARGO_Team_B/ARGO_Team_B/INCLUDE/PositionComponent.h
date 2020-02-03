#pragma once
#include "Component.h"
class PositionComponent : public Component
{
public:
	PositionComponent(int t_x, int t_y);
	~PositionComponent();
	int getPositionX();
	int getPositionY();
	void setPosition(int t_x, int t_y);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
private:
	int m_currentX;
	int m_currentY;
};