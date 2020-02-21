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
	Xbox360Controller* m_controller;

	ControlComponent(Entity & t_gameObject);
	~ControlComponent();
	void handleInput();
	void controlInteract(PlayerComponent* t_player);
	void controlUp(PositionComponent* t_pos);
	void controlDown(PositionComponent* t_pos);
	void controlLeft(PositionComponent* t_pos);
	void controlRight(PositionComponent* t_pos);


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