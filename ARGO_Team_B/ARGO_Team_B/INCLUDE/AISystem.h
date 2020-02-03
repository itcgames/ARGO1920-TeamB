#pragma once

#include <SDL.h>
#include "System.h"
#include "PositionComponent.h"

class AISystem : public System
{
public:
	AISystem();
	~AISystem();
	void updateComponent(Component* component) override;
private:
};
