#pragma once
#include "Component.h"
#include <vector>
class Factory {
public:
	virtual Entity* CreatePlayer(const int t_num, const Level* t_level) = 0;
	virtual Entity* CreateButton() = 0;
	virtual Entity* CreateTrap() = 0;
	virtual Entity* CreateGoal() = 0;
	virtual Entity* CreateGame() = 0;
};
