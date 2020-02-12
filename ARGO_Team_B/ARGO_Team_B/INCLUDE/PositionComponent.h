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
	float getVeloX() { return m_velocityX;}
	float getVeloY() { return m_velocityY; }
	void setPosition(float t_x, float t_y);
	void setVelo(float t_x, float t_y);

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
private:
	const float MAX_VELO = 10;
	const float INC_VELO = 0.5f;

	float m_velocityX;
	float m_velocityY;
	float m_currentX;
	float m_currentY;
};
#endif // !POS
