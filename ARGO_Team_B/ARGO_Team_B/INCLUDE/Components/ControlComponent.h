#ifndef CONTROL_COMPONENT_H
#define CONTROL_COMPONENT_H

#include "Component.h"
#include "Command.h"

#include "PositionComponent.h"
#include "Xbox360Controller.h"
#include "Entity.h"

class ControlComponent : public Component
{
public:
	static int s_controlID;
	ControlComponent(Entity & t_gameObject);
	~ControlComponent();

	void handleInput();
private:
	int m_compNum;

	Xbox360Controller* m_controller;
	Entity& m_entity;

	/// <summary>
	/// Commands
	/// </summary>
	Command* p_walkUp;
	Command* p_walkDown;
	Command* p_walkLeft;
	Command* p_walkRight;
	Command* p_interact;

};

#endif // !CONTROL_cOMPONENT_H
