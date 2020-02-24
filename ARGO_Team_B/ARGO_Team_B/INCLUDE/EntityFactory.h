#pragma once

#include "Component.h"
#include "TestBotBehaviourComponent.h"
#include "TrapComponent.h"
#include "ButtonComponent.h"
#include "PlayerComponent.h"
#include "HealthComponent.h"
#include "GoalComponent.h"
#include "BombComponent.h"
#include "GameComponent.h"

#include "FactoryInterface.h"


class EntityFactory : public Factory {
public:

	Entity* CreatePlayer(const int t_num, const Level* t_level) override {
		Entity* rat = new Entity;
		rat->init(EntityType::Rat);
		rat->addComponent(new PlayerComponent(t_num), Types::Player); // This must allways be first added
		rat->addComponent(new HealthComponent(100), Types::Health);
		rat->addComponent(new PositionComponent(t_level->m_player[t_num - 1].x, t_level->m_player[t_num - 1].y), Types::Position);
		rat->addComponent(new CollisionComponent(*rat, 30.0f, RAT_H, RAT_W), Types::Collider);
		rat->addComponent(new ControlComponent(*rat), Types::Control);
		return rat;
	}
	Entity* CreateDoor() {
		Entity* e = new Entity;
		e->init(EntityType::Default);
		return e;
	}
	Entity* CreateTrap() {
		Entity* e = new Entity;
		e->init(EntityType::Spike);
		return e;
	}
	Entity* CreateButton() {
		Entity* e = new Entity;
		e->init(EntityType::Default);
		return e;
	}
	Entity* CreateGoal() {
		Entity* e = new Entity;
		e->init(EntityType::Default);
		return e;
	}
	Entity* CreateGame() {
		Entity* e = new Entity;
		e->init(EntityType::Default);
		return e;
	}
};
