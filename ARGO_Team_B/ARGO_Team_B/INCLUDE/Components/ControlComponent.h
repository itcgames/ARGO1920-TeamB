#ifndef CONTROL_COMPONENT_H
#define CONTROL_COMPONENT_H

#include "Component.h"
#include "Command.h"


#include "PositionComponent.h"
#include "PlayerComponent.h"
#include "Xbox360Controller.h"
#include "Entity.h"

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
	MovingState m_moving;
	static int s_controlID;
	ControlComponent(Entity & t_gameObject);
	~ControlComponent();
	void update(float dt);
	void handleInput();
private:
	void moveUp();
	void moveLeft();
	void moveRight();
	void moveDown();

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
