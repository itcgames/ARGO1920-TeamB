#include "GoalComponent.h"

GoalComponent::GoalComponent():
	m_alive(true)
{
}


GoalComponent::~GoalComponent()
{
}

bool GoalComponent::getAlive()
{
	return m_alive;
}

void GoalComponent::setAlive(bool t_alive)
{
	m_alive = t_alive;
}
int GoalComponent::getId()
{
	return m_id;
}

void GoalComponent::setId(bool t_id)
{
	m_id = t_id;
}
