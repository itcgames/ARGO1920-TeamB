#pragma once
#include <SDL.h>
#include "System.h"
#include "PositionComponent.h"

class ControlSystem : public System
{
public:
	ControlSystem();
	~ControlSystem();
	void updateComponent(Component* component) override;
	void handleInput(SDL_Keycode key);
};