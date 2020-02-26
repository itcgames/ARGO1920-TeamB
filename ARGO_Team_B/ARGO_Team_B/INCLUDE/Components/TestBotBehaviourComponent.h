#ifndef TEST_BOT_BEHAVIOUR_COMPONENT_H
#define TEST_BOT_BEHAVIOUR_COMPONENT_H

#include "AISystem.h"
#include "Component.h"
#include "BehaviourTree.h"
#include "Command.h"

#include "StateMachineSystem.h"
#include "Enums.h"

#include "ControlComponent.h"

#include "Xbox360Controller.h"
#include "Entity.h"

struct CheeseStruct {
	int distanceToPlayer;
	SDL_Point position;
	bool IsCollected;
};

class TestBotBehaviourComponent : public Component
{
public:
	TestBotBehaviourComponent(Entity& t_gameObject);
	~TestBotBehaviourComponent();
	void update();

	BehaviourTree m_behaviorTree;
	BehaviourTree::Selector m_selector[4];
	BehaviourTree::Sequence m_sequence[5];


private:
	int i = 0;
	Entity& m_entity;
	Command* p_walkUp;
	Command* p_walkDown;
	Command* p_walkLeft;
	Command* p_walkRight;
	Command* p_interact;
};

#endif // !TEST_BOT_BEHAVIOUR_COMPONENT_H