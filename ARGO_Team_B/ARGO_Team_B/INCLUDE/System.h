#pragma once

#include"Component.h"
#include"Entity.h"
#include<vector>
#include "AnimatedSpriteComponent.h"
class System {
public:
	System();
	virtual ~System();

	virtual void update();
	virtual void updateComponent(Component* c);
	virtual void addEntity(Entity e);
protected:
	std::vector<Entity> entities;
	
};