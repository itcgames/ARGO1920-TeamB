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

struct PathNode {
	SDL_Point pos;
	SDL_Point ParentPos;
	float gCost;
	float hCost;
	float fCost;
};

inline bool operator < (const PathNode& t_lhs, const PathNode& t_rhs)
{
	return t_lhs.fCost < t_rhs.fCost;
}
class TestBotBehaviourComponent : public Component
{
public:
	TestBotBehaviourComponent(std::vector<Entity*>& t_entities, Entity& t_gameObject, Level& t_level);
	TestBotBehaviourComponent(Entity& t_gameObject, Level& t_level);
	~TestBotBehaviourComponent();
	void update();

	float distanceFromPlayer(PositionComponent* pos, PositionComponent* pos2);
	void wander();
	void moveToGoal(GoalStruct* t_goal);
	void moveToGoal(int x, int y);
	GoalStruct* FindClosest(std::vector<GoalStruct*> m_goals);

	std::vector<GoalStruct*> m_cheeses;
	std::vector<GoalStruct*> m_bombs;

	BehaviourTree m_behaviourTree;
	BehaviourTree::Selector m_selector[4];
	BehaviourTree::Sequence m_sequence[5];

	GoalStruct* m_TargetCheese;
	GoalStruct* m_TargetBomb;

	Level& m_level;

	/// <summary>
	/// A* Functions
	/// </summary>
	static const int MAXSTEP = 30;

	bool IsNodeValid(int x, int y);
	bool isDestNode(int x, int y, PathNode t_DestNode);
	double calculateH(int x, int y, PathNode(t_dest));
	vector<PathNode> aStar(PathNode start, PathNode dest);
	vector<PathNode> makePath(array<array<PathNode, (SCR_H / MAXSTEP)>, (SCR_W / MAXSTEP) > t_map, PathNode t_dest);

	PathNode* m_startNode;
	PathNode* m_destNode;
	std::vector<PathNode> m_pathWay;

	PathNode* objectToNode(GoalStruct t_struct);
	PathNode* setStartNode();

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