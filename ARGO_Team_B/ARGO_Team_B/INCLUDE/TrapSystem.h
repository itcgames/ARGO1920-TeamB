#pragma once
#include "System.h"
#include "PositionComponent.h"
#include "ButtonComponent.h"
#include "TrapComponent.h"

class TrapSystem : public System {
public:
	TrapSystem();
	~TrapSystem();

	void updateComponent(Component* c) override;
	void setStates();
};