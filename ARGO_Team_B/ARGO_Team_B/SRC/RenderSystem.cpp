#include "RenderSystem.h"

RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::addEntity(Entity e)
{
	entities.push_back(e);
}

void RenderSystem::updateComponent(Component* c)
{
}

void RenderSystem::draw()
{
	for (Entity& e : entities)
	{
		for (Component* c : e.getComponents())
		{
			RenderComponent* rendComp = dynamic_cast<RenderComponent*>(c);
			if (rendComp != nullptr)
			{
				for (Component* c2 : e.getComponents())
				{
					PositionComponent* posComp = dynamic_cast<PositionComponent*>(c2);			
					if (posComp != nullptr)
					{
						for (Component* c3 : e.getComponents())
						{
							HealthComponent* healthComp = dynamic_cast<HealthComponent*>(c3);

							TrapComponent* trapComp = dynamic_cast<TrapComponent*>(c3);

							ButtonComponent* btnComp = dynamic_cast<ButtonComponent*>(c3);

							DoorComponent* doorcomp = dynamic_cast<DoorComponent*>(c3);

							GoalComponent* goalComp = dynamic_cast<GoalComponent*>(c3);

							if (healthComp != nullptr)
							{
								if (healthComp->getAlive() == true)
								{
									rendComp->draw((int)posComp->getPositionX(), (int)posComp->getPositionY());
								}
							}
							else if (trapComp != nullptr){
								if (trapComp->getAlive()) {
									rendComp->draw((int)posComp->getPositionX(), (int)posComp->getPositionY());
								}
							}
							else if (btnComp != nullptr) {
								if (btnComp->getAlive()) {
									rendComp->draw((int)posComp->getPositionX(), (int)posComp->getPositionY());
								}
							}
							else if (doorcomp != nullptr) {
								if (!doorcomp->getGreenDoor() || !doorcomp->getRedDoor()) {
									rendComp->draw((int)posComp->getPositionX(), (int)posComp->getPositionY());
								}
							}
							else if (goalComp != nullptr) {
								if (goalComp->getAlive())
								{
									rendComp->draw((int)posComp->getPositionX(), (int)posComp->getPositionY());
								}

							}
						}		
					}
				}
			}
		}
	}
}
