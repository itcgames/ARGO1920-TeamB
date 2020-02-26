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

#include <vector>
#include <math.h>

struct GoalStruct {
	float distanceToPlayer;
	SDL_Point position;
	bool isActive = true;
};

struct CheeseStruct : public GoalStruct{
	float distanceToPlayer;
	SDL_Point position;
	bool isCollected;
};

struct BombStruct :public GoalStruct
{
	float disToPlayer;
	SDL_Point location;
	bool isActive;
};

struct ButtonStruct : public GoalStruct
{
	float disToPlayer;
	SDL_Point location;
	bool isActive;
};


class TestBotBehaviourComponent : public Component
{
public:
	TestBotBehaviourComponent(std::vector<Entity*>& t_entities, Entity& t_gameObject);
	TestBotBehaviourComponent(Entity& t_gameObject);
	~TestBotBehaviourComponent();
	void update();

	float distanceFromPlayer(PositionComponent* pos, PositionComponent* pos2);
	void wander();
	void moveToGoal(GoalStruct* t_goal);
	GoalStruct* FindClosest(std::vector<GoalStruct*> m_goals);

	std::vector<GoalStruct*> m_cheeses;
	std::vector<GoalStruct*> m_bombs;

	BehaviourTree m_behaviourTree;
	BehaviourTree::Selector m_selector[4];
	BehaviourTree::Sequence m_sequence[5];

	GoalStruct* m_TargetCheese;
	GoalStruct* m_TargetBomb;

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