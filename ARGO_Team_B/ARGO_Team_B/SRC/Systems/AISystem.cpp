#include "AISystem.h"

AISystem::AISystem() {}

AISystem::~AISystem() {}

void AISystem::updateComponent(Component* component)
{
	PositionComponent* pc = dynamic_cast<PositionComponent*>(component);
	if (nullptr != pc)
	{
		int x = pc->getPositionX();
		int y = pc->getPositionY();
		x += 3;
		if (x > 1080)
		{
			x = 0;
		}
		pc->setPosition(x,y);
	}
}