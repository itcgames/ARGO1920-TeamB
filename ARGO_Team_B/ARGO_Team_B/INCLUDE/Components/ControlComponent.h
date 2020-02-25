#ifndef CONTROL_COMPONENT_H
#define CONTROL_COMPONENT_H

#include "Component.h"
#include "Command.h"
#include "StateMachineSystem.h"
#include "Enums.h"
#include "PositionComponent.h"
#include "PlayerComponent.h"
#include "Xbox360Controller.h"
#include "Entity.h"
#include "CollisionSystem.h"
enum class MovingState {
	Up,
	Down,
	Left,
	Right,
	Idle
};

class ControlComponent : public Component
{
public:
	static int s_controlID;

	ControlComponent(Entity& t_gameObject, int controller);
	ControlComponent(Entity & t_gameObject);
	~ControlComponent();

	void handleInput(SDL_Renderer * t_renderer,std::vector<ParticleSystem*>&t_ps, float dt);
	void controlInteract(PlayerComponent* t_player);
	void controlUp(PositionComponent* t_pos);
	void controlDown(PositionComponent* t_pos);
	void controlLeft(PositionComponent* t_pos);
	void controlRight(PositionComponent* t_pos);

	Xbox360Controller* m_controller;
	Xbox360Controller* getController() { return m_controller; }

private:


	int m_compNum;
	Entity& m_entity;
	MacroCommand* m_commandSquence = new MacroCommand();
	Command* p_walkUp;
	Command* p_walkDown;
	Command* p_walkLeft;
	Command* p_walkRight;
	Command* p_interact;
};

#endif // !CONTROL_COMPONENT_H