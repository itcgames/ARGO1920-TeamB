#include "HealthComponent.h"

HealthComponent::HealthComponent(int t_health)
{
	m_currentHealth = t_health;
	m_alive = true;
}

HealthComponent::~HealthComponent()
{
}

int HealthComponent::getHealth()
{
	return m_currentHealth;
}

void HealthComponent::setHealth(int t_health)
{
	m_currentHealth = t_health;
}

bool HealthComponent::getAlive()
{
	return m_alive;
}

void HealthComponent::dead()
{
	m_alive = false;
}
