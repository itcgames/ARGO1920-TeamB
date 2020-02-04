#pragma once
#include <SDL.h>
#include <iostream>
#include "System.h"
#include "PositionComponent.h"

#include "xbox360Controller.h"

class ControlSystem : public System
{
private:
	Xbox360Controller* m_controller;
public:
	ControlSystem();
	~ControlSystem();
	void updateComponent(Component* component) override;
	void handleInput();
	void handleInput(SDL_Keycode key);
	int i = 0;
};