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

class ComponentFactory : public Factory {
public:
	Component* CreatePlayer(int t_num) {
		return new PlayerComponent(t_num);
	}
	Component* CreateHealth() {
		return new HealthComponent(100);
	}
	Component* CreatePosition(float t_x, float t_y) {
		return new PositionComponent(t_x, t_y);
	}
	Component* CreateCollision(Entity& t_gameObject, float t_diameter, int t_width, int t_height) {
		return new CollisionComponent(t_gameObject, t_diameter, t_width, t_height);
	}
	Component* CreateControl(Entity& t_gameObject) {
		return new ControlComponent(t_gameObject);
	}
	Component* CreateRender(const char* t_name, int t_width, int t_height, SDL_Renderer* t_renderer) {
		return new RenderComponent(t_name, t_width, t_height, t_renderer);
	}
	Component* CreateAnimatedSprite(const char* t_texture, int t_height, int t_width, int t_noOfFrames, float t_time, SDL_Renderer* t_renderer) {
		return new AnimatedSpriteComponent(t_texture, t_height, t_width, t_noOfFrames, t_time, t_renderer);
	}
	Component* CreateTestBotBehaviour(Entity& t_gameObject) {
		return new TestBotBehaviourComponent(t_gameObject);
	}
	Component* CreateButton(bool t_init, int t_id, int t_type) {
		return new ButtonComponent(t_init, t_id, t_type);
	}
	Component* CreateTrap(bool t_init, int t_id) {
		return new TrapComponent(t_init, t_id);
	}
	Component* CreateGoal() {
		return new GoalComponent();
	}
	Component* CreateBomb() {
		return new BombComponent();
	}
	Component* CreateGame() {
		return new GameComponent();
	}
};
