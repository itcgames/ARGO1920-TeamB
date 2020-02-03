#include "../INCLUDE/ControlSystem.h"

ControlSystem::ControlSystem() {}

ControlSystem::~ControlSystem() {}
void ControlSystem::updateComponent(Component* c)
{
	for (Entity& e : entities)
	{
		PositionComponent* posComp = dynamic_cast<PositionComponent*>(c);
		if (posComp != nullptr)
		{

		}
	}
}

void ControlSystem::handleInput(SDL_Keycode key)
{
	for (Entity& e : entities)
	{
		for (Component* c : e.getComponents())
		{
			PositionComponent* posComp = dynamic_cast<PositionComponent*>(c);
			if (posComp != nullptr)
			{
				switch (key)
				{
				case SDLK_a:
					posComp->moveLeft();
					break;
				case SDLK_d:
					posComp->moveRight();
					break;
				case SDLK_w:
					posComp->moveUp();
					break;
				case SDLK_s:
					posComp->moveDown();
					break;
				default:
					break;
				}

			}
		}
	}
	
}
