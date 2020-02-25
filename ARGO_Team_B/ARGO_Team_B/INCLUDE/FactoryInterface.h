#pragma once
#include "Component.h"
#include <vector>
class Factory {
public:
	virtual Entity* CreatePlayer(const int t_num, const Level* t_level) = 0;
	virtual Entity* CreateButton(const int t_num, const float t_x, const float t_y) = 0;
	virtual Entity* CreateTrap(const int t_num, const bool t_alive, const float t_x, float t_y) = 0;
	virtual Entity* CreateCheese(const float t_x, const float t_y) = 0;
	virtual Entity* CreateGame() = 0;
};
