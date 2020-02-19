#ifndef TEST_BOT_BEHAVIOUR_COMPONENT_H
#define TEST_BOT_BEHAVIOUR_COMPONENT_H

#include "AISystem.h"
#include "Component.h"
#include "Command.h"

#include "StateMachineSystem.h"
#include "Enums.h"

#include "PositionComponent.h"
#include "PlayerComponent.h"
#include "Xbox360Controller.h"
#include "Entity.h"

class TestBotBehaviourComponent : public Component
{
public:
	TestBotBehaviourComponent(Entity& t_gameObject);
	~TestBotBehaviourComponent();
	void update();
private:
	Entity& m_entity;
	Command* p_walkUp;
	Command* p_walkDown;
	Command* p_walkLeft;
	Command* p_walkRight;
	Command* p_interact;
};

#endif // !TEST_BOT_BEHAVIOUR_COMPONENT_H