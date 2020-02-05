#ifndef CONTROL_COMPONENT_H
#define CONTROL_COMPONENT_H

#include "Component.h"
#include "PositionComponent.h"
#include "xbox360Controller.h"
class ControlComponent : public Component
{
public:
	static int s_controlID;
	ControlComponent();
	~ControlComponent();

	void handleInput(Component* t_position);
private:
	int m_compNum;

	Xbox360Controller* m_controller;

};

#endif // !CONTROL_cOMPONENT_H