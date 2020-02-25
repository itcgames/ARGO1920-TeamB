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
/// 
/// FOR ALL ENTITY
/// the position component must create before the collision component
/// 
class EntityFactory : public Factory {
public:

	Entity* CreatePlayer(const int t_num, const Level* t_level) override {
		Entity* rat = new Entity;
		rat->init(EntityType::Rat);
		rat->addComponent(new PlayerComponent(t_num), Types::Player); // This must always be first added
		rat->addComponent(new HealthComponent(100), Types::Health);
		rat->addComponent(new PositionComponent(t_level->m_player[t_num - 1].x, t_level->m_player[t_num - 1].y), Types::Position);
		rat->addComponent(new CollisionComponent(*rat, RAT_W, RAT_H, 4), Types::Collider);
		rat->addComponent(new ControlComponent(*rat), Types::Control);
		rat->addComponent(new AnimatedSpriteComponent("./Assets/SpriteSheetIdleMouse.png", RAT_H, RAT_W, 5, 5000), Types::AnimatedSprite);

		return rat;
	}
	Entity* CreateDoor() {
		Entity* e = new Entity;
		e->init(EntityType::Default);
		return e;
	}
	Entity* CreateTrap(const int t_num, const bool t_alive, const float t_x, float t_y) {
		Entity* spike = new Entity;
		spike->init(EntityType::Spike);
		spike->addComponent(new TrapComponent(t_alive, t_num), Types::Traps);
		spike->addComponent(new PositionComponent(t_x , t_y), Types::Position);
		spike->addComponent(new CollisionComponent(*spike, RAT_W, RAT_W), Types::Collider);
		spike->addComponent(new RenderComponent("./Assets/Spike.png", 30, 30, 30, 30), Types::Render);
		return spike;
	}
	Entity* CreateButton(const int t_num, const float t_x, float t_y) {
		Entity* button = new Entity;
		button->init(EntityType::Default);
		button->addComponent(new ButtonComponent(false, t_num, 1), Types::Button);
		button->addComponent(new PositionComponent(t_x, t_y), Types::Position);
		button->addComponent(new CollisionComponent(*button, RAT_W, RAT_W), Types::Collider);
		button->addComponent(new RenderComponent("./Assets/Button.png", 30, 30, 30, 30), Types::Render);

		return button;
	}
	Entity* CreateCheese(const float t_x, const float t_y) {
		Entity* cheese = new Entity;
		cheese->init(EntityType::Default);
		cheese->addComponent(new GoalComponent(), Types::Goal);
		cheese->addComponent(new PositionComponent(t_x, t_y), Types::Position);
		cheese->addComponent(new CollisionComponent(*cheese, 30.0f, 30, 30), Types::Collider);
		cheese->addComponent(new RenderComponent("./Assets/cheese.png", 30, 30, 30, 30), Types::Render);
		return cheese;
	}
	Entity* CreateBomb(const float t_x, const float t_y) {
		Entity* bomb = new Entity;
		bomb->init(EntityType::Default);
		bomb->addComponent(new BombComponent(), Types::Bomb);
		bomb->addComponent(new PositionComponent(t_x, t_y), Types::Position);
		bomb->addComponent(new CollisionComponent(*bomb, 30.0f, 30, 30), Types::Collider);
		bomb->addComponent(new RenderComponent("./Assets/bomb.png", 30, 30, 300, 300), Types::Render);
		return bomb;
	}
	Entity* CreateGame() {
		Entity* game = new Entity;
		game->init(EntityType::Default);
		game->addComponent(new GameComponent(), Types::Game);
		game->addComponent(new PositionComponent((float)SCR_W / 2, (float)SCR_H / 2), Types::Position);
		game->addComponent(new RenderComponent("Assets\\cheese.png", 30, 30, 30, 30), Types::Render);
		return game;
	}
};
