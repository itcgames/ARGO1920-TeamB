#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H


#include "Component.h"
#include <iostream>
class HealthComponent : public Component
{
public:
	HealthComponent(int t_health);
	~HealthComponent();
	int getHealth();
	void setHealth(int t_health);
	bool getAlive();
	void dead();
private:
	int m_currentHealth;
	bool m_alive;
};

#endif // !HEALTHCOMPONENT_H