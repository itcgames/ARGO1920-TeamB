#ifndef BOMBSYSTEM
#define BOMBSYSTEM
#pragma once

#include "System.h"

#include "BombComponent.h"
#include "PlayerComponent.h"
#include "PositionComponent.h"
#include "CollisionComponent.h"

class BombSystem : public System {
public:
	BombSystem();
	~BombSystem();

	void updateComponent(Component* c) override;
	void updateComponent(float dt);

private:
	vector<Entity> m_playerEntitys;
	vector<Entity> m_bombEntitys;

	void searchEntities();
};

#endif