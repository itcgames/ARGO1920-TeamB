#ifndef RENDER_SYSTEM
#define RENDER_SYSTEM

#include<iostream>
#include "System.h"
#include "Entity.h"
#include "RenderComponent.h"
#include "PositionComponent.h"
#include "HealthComponent.h"
#include "TrapComponent.h"
#include "ButtonComponent.h"
#include "DoorComponent.h"
#include "GoalComponent.h"

class RenderSystem : public System {
public:
	RenderSystem();
	~RenderSystem();
	void addEntity(Entity e)override;
	void updateComponent(Component* c)override;
	void draw();
private:
};
#endif // !RENDER_SYSTEM