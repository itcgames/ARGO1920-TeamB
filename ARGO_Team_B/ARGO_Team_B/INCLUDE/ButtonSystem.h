#ifndef BUTTONSYSTEM
#define BUTTONSYSTEM

#pragma once
#include "System.h"
#include "PositionComponent.h"
#include "ButtonComponent.h"
#include "TrapComponent.h"
#include "DoorComponent.h"

class ButtonSystem : public System {
public:
	ButtonSystem();
	~ButtonSystem();

	void updateComponent(Component* c) override;
	void setObjectStates();

};
#endif