#ifndef RENDER_SYSTEM
#define RENDER_SYSTEM

#include<iostream>
#include"System.h"
#include"RenderComponent.h"
#include"Entity.h"
#include"PositionComponent.h"
#include "HealthComponent.h"

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