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
	AnimatedSpriteComponent* cont = dynamic_cast<AnimatedSpriteComponent*>(c);

	if (cont != NULL)
	{
		cont->update();
	}
}

void System::addEntity(Entity e)
{
	entities.push_back(e);
}
