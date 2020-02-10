#include "System.h"

System::System()
{
}

System::~System()
{
}

void System::update()
{
	for (Entity& e : entities)
	{
		for (auto& c : e.getComponents())
		{
			updateComponent(c);
		}
	}
}

void System::updateComponent(Component* c)
{
}

void System::addEntity(Entity e)
{
	entities.push_back(e);
}
