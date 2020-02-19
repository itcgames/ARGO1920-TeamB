#ifndef AI_SYSTEM
#define AI_SYSTEM

#include <SDL.h>
#include "System.h"
#include "TestBotBehaviourComponent.h"

class AISystem : public System
{
public:
	AISystem();
	~AISystem();
	void updateComponent(Component* component) override;
private:
};

#endif // !AI_SYSTEM
