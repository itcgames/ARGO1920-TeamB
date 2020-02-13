#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "System.h"
#include "AnimatedSpriteComponent.h"
#include "PositionComponent.h"

class StateMachineSystem : public System
{
public:
	StateMachineSystem();
	~StateMachineSystem();

	void updateComponent(Component* c) override;

	void setCurrent( /* State */);
	void setPrevious(/* State */);

};

#endif // !STATEMACHINE_H

