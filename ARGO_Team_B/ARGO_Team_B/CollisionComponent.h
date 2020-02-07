#ifndef COLLISION_COMPONENT
#define COLLISION_COMPONENT

#include "Component.h"
#include <iostream>
class CollisionComponent : public Component
{
public:
	CollisionComponent(int t_health);
	~CollisionComponent();
	int getHealth();
	void setHealth(int t_health);
	bool getAlive();
	void dead();
private:
	int m_currentHealth;
	bool m_alive;
};
#endif // !COLLISION_COMPONENT