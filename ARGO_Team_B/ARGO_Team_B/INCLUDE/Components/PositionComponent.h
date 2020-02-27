#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "Component.h"
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "Component.h"
#include <math.h>
#include "Level.h"

class PositionComponent : public Component
{
public:
	PositionComponent(float t_x, float t_y);
	~PositionComponent();

	void movementUpdate(float dt);

	float getPositionX();
	float getPositionY();
	float getVeloX() { return m_velocityX; }
	float getVeloY() { return m_velocityY; }
	void setPosition(float t_x, float t_y);
	void setVelo(float t_x, float t_y);

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void slowDownX();
	void slowDownY();

	void backToPreviousePos();
	void setPreviousePos();
	void setPreviouseAngle();

	void setangle(double t_angle);

	double getangle();

	float getLastX() { return m_lastX; }
	float getLastY() { return m_lastY; }

	void backToStart();

	bool m_isMoving{ false };

	void reset(int t_num, Level* t_level);

private:
	const int MAX_VELO = 8;
	const float INC_VELO = 0.5f;

	float m_velocityX;
	float m_velocityY;

	float m_acceleration;

	float m_currentX;
	float m_currentY;

	double m_angle = 0;

	float m_startX;
	float m_startY;

	float m_lastX;
	float m_lastY;
	double m_lastAngle;


};
#endif // !POS
