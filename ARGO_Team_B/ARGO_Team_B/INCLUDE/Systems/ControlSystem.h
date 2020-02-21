#ifndef CONTROL_SYSTEM
#define CONTROL_SYSTEM

#include <SDL.h>
#include <iostream>
#include "System.h"
#include "PositionComponent.h"
#include "ControlComponent.h"
#include "StateMachineSystem.h"


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
	void handleInput(float dt);
	void handleInput(SDL_Keycode key);

	int contNum= 0;
	int i = 0;
};

#endif // !CONTROL_SYSTEM