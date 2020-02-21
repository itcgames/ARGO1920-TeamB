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

class ControlComponent : public Component
{
public:
	static int s_controlID;

	ControlComponent(Entity& t_gameObject, int controller);
	ControlComponent(Entity & t_gameObject);
	~ControlComponent();

	void initStateSystem(StateMachineSystem* t_stateSystem);
	void handleInput();
	void controlInteract(PlayerComponent* t_player);
	void controlUp(PositionComponent* t_pos);
	void controlDown(PositionComponent* t_pos);
	void controlLeft(PositionComponent* t_pos);
	void controlRight(PositionComponent* t_pos);

	Xbox360Controller* m_controller;
	void handleInput(StateMachineSystem& t_stateSystem);
	Xbox360Controller* getController() { return m_controller; }

private:
	void moveUp();
	void moveLeft();
	void moveRight();
	void moveDown();

	StateMachineSystem* m_stateSystem;
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