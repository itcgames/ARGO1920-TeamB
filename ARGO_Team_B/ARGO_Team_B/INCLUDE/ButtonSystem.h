#pragma once
#include "System.h"
#include "PositionComponent.h"
#include "ButtonComponent.h"
#include "TrapComponent.h"

class ButtonSystem : public System {
public:
	ButtonSystem();
	~ButtonSystem();

	void updateComponent(Component* c) override;
	void setStates();
};