#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "System.h"

class StateMachineSystem : public System
{
public:
	StateMachineSystem();
	~StateMachineSystem();

	void setCurrent( /* State */);
	void setPrevious(/* State */);

};

#endif // !STATEMACHINE_H

