#ifndef CONTROL_SYSTEM_H
#define CONTROL_SYSTEM_H

#include <SDL.h>
#include <iostream>
#include "System.h"
#include "PositionComponent.h"
#include "ControlComponent.h"


#include <vector>
#include "xbox360Controller.h"



class ControlSystem : public System
{
private:
	int NOOFPLAYERS = 4;

	std::vector<Xbox360Controller*> m_controllers;
public:
	ControlSystem();
	~ControlSystem();
	void updateComponent(Component* c) override;
	void handleInput();
	void handleInput(SDL_Keycode key);

	int contNum= 0;
};

#endif // !CONTROL_SYSTEM_H
