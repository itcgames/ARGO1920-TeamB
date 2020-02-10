#ifndef GOAL_COMPONENT_H
#define GOAL_COMPONENT_H

#include "Component.h"

class GoalComponent : public Component 
{
public:

	GoalComponent();

	~GoalComponent();

	bool getAlive();
	void setAlive(bool t_alive);

	int getId();
	void setId(bool t_id);
private:

	bool m_alive;
	int m_id;
};
#endif // !GOAL_COMPONENT_H
