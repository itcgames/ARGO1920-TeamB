#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "Component.h"
#include <stdlib.h>
#include <time.h>
#include "Component.h"
class PositionComponent : public Component
{
public:
	PositionComponent(float t_x, float t_y);
	~PositionComponent();
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

	void backToPreviousePos();
	void setPreviousePos();

	void setangle(double t_angle);

	double getangle();

	float getLastX() { return m_lastX; }
	float getLastY() { return m_lastY; }

	void backToStart();
private:
	const float MAX_VELO = 10;
	const float INC_VELO = 0.5f;

	float m_velocityX;
	float m_velocityY;
	float m_currentX;
	float m_currentY;

	int m_acceleration;
	double m_angle = 0;

	float m_startX;
	float m_startY;

	float m_previouseX;
	float m_previouseY;

	float m_lastX;
	float m_lastY;
};
#endif // !POS
