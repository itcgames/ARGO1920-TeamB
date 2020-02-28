#include "TestBotBehaviourComponent.h"

TestBotBehaviourComponent::TestBotBehaviourComponent(std::vector<Entity*>& t_entities, Entity& t_gameObject, Level& t_level) :
	m_entity(t_gameObject),
	m_level(t_level)
{
	m_entity.isBot = true;
	for (Entity* e : t_entities)
	{
		if (e->getType() == Types::Goal)
		{
			PositionComponent* posComp = dynamic_cast<PositionComponent*>(e->getComponent(Types::Position));
			GoalComponent* goalComp = dynamic_cast<GoalComponent*>(e->getComponent(Types::Goal));

			GoalStruct* cheese = new GoalStruct;
			cheese->isActive = goalComp->getAlive();
			cheese->position.x = posComp->getPositionX();
			cheese->position.y = posComp->getPositionY();
			cheese->distanceToPlayer = distanceFromPlayer(posComp, static_cast<PositionComponent*>(m_entity.getComponent(Types::Position)));

			m_cheeses.push_back(cheese);
		}
		if (e->getType() == Types::Bomb)
		{
			PositionComponent* posComp = dynamic_cast<PositionComponent*>(e->getComponent(Types::Position));
			BombComponent* bombComp = dynamic_cast<BombComponent*>(e->getComponent(Types::Bomb));

			GoalStruct* bomb = new GoalStruct;
			bomb->isActive = !(bombComp->isPlayerOwnedBomb());
			
			bomb->position.x = posComp->getPositionX();
			bomb->position.y = posComp->getPositionY();
			bomb->distanceToPlayer = distanceFromPlayer(posComp, static_cast<PositionComponent*>(m_entity.getComponent(Types::Position)));

			m_bombs.push_back(bomb);
		}
	}
	m_TargetCheese = FindClosest(m_cheeses);
	m_TargetBomb = FindClosest(m_bombs);
	if (m_TargetBomb->distanceToPlayer < m_TargetCheese->distanceToPlayer)
	{
		m_mainTarget = m_TargetBomb;
	}
	else
	{
		m_mainTarget = m_TargetCheese;
	}
	m_destNode = objectToNode(*m_mainTarget);
	m_startNode = setStartNode();
	m_pathWay = aStar(*m_startNode, *m_destNode);

}

TestBotBehaviourComponent::TestBotBehaviourComponent(Entity& t_gameObject, Level& t_level) :
	m_entity{ t_gameObject },
	m_level(t_level)
{
		
}

TestBotBehaviourComponent::~TestBotBehaviourComponent()
{
}

/// <summary>
/// ************************************* UPDATE FUNCTION **************************************************
/// </summary>
void TestBotBehaviourComponent::update()
{
	ControlComponent* cont = dynamic_cast<ControlComponent*>(m_entity.getComponent(Types::Control));
	PlayerComponent* playercomp = dynamic_cast<PlayerComponent*>(m_entity.getComponent(Types::Player));

	if (stepTimer >= stepTimerMax)
	{
		if (step < m_pathWay.size())
		{
			moveToGoal(m_pathWay.at(step).pos.x, m_pathWay.at(step).pos.y);
			step++;
		}
		else
		{
			if (m_mainTarget == m_TargetBomb)
			{
				cont->controlInteract(playercomp);
				m_TargetBomb->isActive = false;
			}
			else if (m_mainTarget == m_TargetCheese)
			{
				m_TargetCheese->isActive = false;
			}
			step = 0;

			m_TargetCheese = FindClosest(m_cheeses);
			m_TargetBomb = FindClosest(m_bombs);
			if (m_TargetCheese == nullptr || m_TargetBomb == nullptr)
			{
				if (m_TargetBomb != nullptr)
				{
					m_mainTarget = m_TargetBomb;
				}
				else if (m_TargetCheese != nullptr)
				{
					m_mainTarget = m_TargetCheese;
				}
			}
			else if (m_TargetBomb->distanceToPlayer < m_TargetCheese->distanceToPlayer)
			{
				m_mainTarget = m_TargetBomb;
			}
			else
			{
				m_mainTarget = m_TargetCheese;
			}
			m_destNode = objectToNode(*m_mainTarget);
			m_startNode = setStartNode();
			m_pathWay = aStar(*m_startNode, *m_destNode);
		}
		stepTimer = 0;
	}
	else
	{
		stepTimer++;
	}


	//PlayerComponent* playerComp = dynamic_cast<PlayerComponent*>(m_entity.getComponent(Types::Player));
	//PositionComponent* posComp = dynamic_cast<PositionComponent*>(m_entity.getComponent(Types::Position));
	//ControlComponent *control = dynamic_cast<ControlComponent*>(m_entity.getComponent(Types::Control));
	////reset interact 
	//playerComp->setInteract(false);
	//if (playerComp->getMoveable() && !playerComp->getDizzy()) {

	//	if (control != nullptr)
	//	{
	//		//if (i == 0) {

	//			//posComp->moveLeft();
	//			//posComp->moveRight();

	//			control->controlLeft(posComp);
	//			//control->controlUp(posComp);
	//			control->controlRight(posComp);
	//			//control->controlDown(posComp);

	//			//i++;
	//		// }
	//	}
	//	else if (!playerComp->getMoveable()) {
	//		posComp->backToPreviousePos();
	//		playerComp->setMoveable(true);
	//	}
	//}
}

/// <summary>
/// ************************************** GET DISTANCE BETWENN 2 POINTS *************************************
/// </summary>
float TestBotBehaviourComponent::distanceFromPlayer(PositionComponent* pos, PositionComponent* pos2)
{
	if (pos != NULL && pos2 != NULL)
	{
		return sqrt((pow(pos->getPositionX() - pos2->getPositionX(), 2) + (pow(pos->getPositionY() - pos2->getPositionY(), 2))));
	}
	else 
	{
		return INFINITY;
	}
}


float TestBotBehaviourComponent::distanceFromPlayer(int targetx, int targety, PositionComponent* pos2)
{
	if (pos2 != NULL)
	{
		return sqrt((pow(targetx - pos2->getPositionX(), 2) + (pow(targety- pos2->getPositionY(), 2))));
	}
	else
	{
		return INFINITY;
	}
}

/// <summary>
/// *************************************** WANDER FUNCTION *********************************************
/// </summary>
void TestBotBehaviourComponent::wander()
{
	PlayerComponent* playerComp = dynamic_cast<PlayerComponent*>(m_entity.getComponent(Types::Player));
	PositionComponent* posComp = dynamic_cast<PositionComponent*>(m_entity.getComponent(Types::Position));
	ControlComponent* control = dynamic_cast<ControlComponent*>(m_entity.getComponent(Types::Control));
	//reset interact 

	int direction = std::rand() % 4;
	playerComp->setInteract(false);
	if (playerComp->getMoveable() && !playerComp->getDizzy()) {

		if (control != nullptr)
		{
			switch (direction)
			{
			case 0:
				control->controlLeft(posComp);
				break;
			case 1:
				control->controlRight(posComp);
				break;
			case 2:
				control->controlDown(posComp);
				break;
			case 3:
				control->controlUp(posComp);
				break;
			default:
				break;
			}
		}
		else if (!playerComp->getMoveable()) {
			posComp->backToPreviousePos();
			playerComp->setMoveable(true);
		}
	}
}


/// <summary>
/// **************************************************** MOVE TO GOAL *********************************************
/// </summary>
void TestBotBehaviourComponent::moveToGoal(GoalStruct* t_goal)
{
	PositionComponent* posComp =  dynamic_cast<PositionComponent*>(m_entity.getComponent(Types::Position));

	float directionAngle = atan2( posComp->getPositionY() - t_goal->position.y, posComp->getPositionX()- t_goal->position.x) * (180/3.14);

	SDL_Point directionVector;
	directionVector.x = (t_goal->position.x + posComp->getPositionX()) / directionAngle;
	directionVector.y = (t_goal->position.y + posComp->getPositionY()) / directionAngle;

	posComp->setPosition(posComp->getPositionX() + directionVector.x, posComp->getPositionY() + directionVector.y);
	posComp->setPreviouseAngle();
	posComp->setangle(directionAngle);

}

void TestBotBehaviourComponent::moveToGoal(int x, int y)
{
	PositionComponent* posComp =  dynamic_cast<PositionComponent*>(m_entity.getComponent(Types::Position));
	AnimatedSpriteComponent* animComp = dynamic_cast<AnimatedSpriteComponent*>(m_entity.getComponent(Types::AnimatedSprite));
	ControlComponent* control = dynamic_cast<ControlComponent*>(m_entity.getComponent(Types::Control));
	wander();

	//animComp->setCurrent(new WalkingState);
	float directionAngle = atan2( posComp->getPositionY() - y , posComp->getPositionX()- x) * (180/3.14);

	SDL_Point directionVector;
	directionVector.x = (x * MAXSTEP + posComp->getPositionX()) / directionAngle;
	directionVector.y = (y * MAXSTEP + posComp->getPositionY()) / directionAngle;
	
	posComp->setPosition(x * MAXSTEP, y * MAXSTEP);
	posComp->setangle(directionAngle);
}
/// <summary>
/// *********************************************** FIND CLOSEST *****************************************
/// </summary>
/// <returns></returns>
GoalStruct* TestBotBehaviourComponent::FindClosest(std::vector<GoalStruct*> t_goals)
{
	PositionComponent* pos = static_cast<PositionComponent*>(m_entity.getComponent(Types::Position));
	GoalStruct* m_closest = nullptr;
	float shortest = FLT_MAX;
	for (GoalStruct* goal : t_goals)
	{
		if (goal->isActive)
		{
			if (pos->getPositionY() < (SCR_H * .5) && goal->position.y < (SCR_H * .5))
			{
				goal->distanceToPlayer = distanceFromPlayer(goal->position.x, goal->position.y, static_cast<PositionComponent*>(m_entity.getComponent(Types::Position)));
				if (goal->distanceToPlayer < shortest && goal->isActive)
				{
					shortest = goal->distanceToPlayer;
					m_closest = goal;
				}
			}
			else if (pos->getPositionY() > (SCR_H * .5) && goal->position.y > (SCR_H * .5))
			{
				goal->distanceToPlayer = distanceFromPlayer(goal->position.x, goal->position.y, static_cast<PositionComponent*>(m_entity.getComponent(Types::Position)));
				if (goal->distanceToPlayer < shortest && goal->isActive)
				{
					shortest = goal->distanceToPlayer;
					m_closest = goal;
				}
			}
		}
	}
	if (m_closest == NULL)
	{
		NoCheese = true;
		return nullptr;
	}
	else
	{
		return m_closest;
	}
}

/// <summary>
/// **************************************** A* Functions *************************************
/// </summary>
bool TestBotBehaviourComponent::IsNodeValid(int x, int y)
{
	for (MazeWallObject& wall : m_level.m_mazeWalls)
	{
		if (x * MAXSTEP == wall.x && y * MAXSTEP == wall.y)
		{
			return false;
		}
	}
	for (MazeWallObject& wall : m_level.m_outerBorders)
	{
		if (x * MAXSTEP >= wall.x && x * MAXSTEP <= wall.x + wall.width &&
			y * MAXSTEP >= wall.y && y * MAXSTEP <= wall.y + wall.height)
		{
			return false;
		}
	}
	return true;
}

/// <summary>
/// ******************************************* CHECXK NODE FOR DESTINATION ***********************
/// </summary>
bool TestBotBehaviourComponent::isDestNode(int x, int y, PathNode t_DestNode)
{
	if (x == t_DestNode.pos.x && y == t_DestNode.pos.y )
	{
		return true;
	}
	return false;
}

/// <summary>
/// *************************************** CALCULATE HEURISTICS *********************************
/// </summary>
double TestBotBehaviourComponent::calculateH(int x, int y, PathNode(t_dest))
{
	double H = (sqrt(pow(x - t_dest.pos.x, 2) + pow(y - t_dest.pos.y, 2)));
	return H;
}

/// <summary>
/// ******************************* A Star Function Definition **********************************	
/// </summary>

vector<PathNode> TestBotBehaviourComponent::aStar(PathNode start, PathNode dest)
{
	vector<PathNode> empty;
	if (IsNodeValid(dest.pos.x, dest.pos.y) == false)
	{
		std::cout << "Destination Not Valid" << std::endl;
		return empty;
	}

	if (isDestNode(start.pos.x, start.pos.y, dest))
	{
		std::cout << "Player at position" << std::endl;
		return empty;
	}

	bool closedList[(SCR_W / MAXSTEP)][(SCR_H / MAXSTEP)];

	array<array<PathNode, (SCR_H / MAXSTEP)>, (SCR_W / MAXSTEP)> fullMap;

	for (int x = 0; x < (SCR_W / MAXSTEP); x++)
	{
		for (int y = 0; y < (SCR_H / MAXSTEP); y++)
		{
			fullMap[x][y].fCost = FLT_MAX;
			fullMap[x][y].gCost = FLT_MAX;
			fullMap[x][y].hCost = FLT_MAX;
			fullMap[x][y].ParentPos.x = -1;
			fullMap[x][y].ParentPos.y = -1;
			fullMap[x][y].pos.x = x;
			fullMap[x][y].pos.y = y;

			closedList[x][y] = false;

		}
	}

	int x = start.pos.x;
	int y = start.pos.y;
	fullMap[x][y].fCost = 0.0;
	fullMap[x][y].gCost = 0.0;
	fullMap[x][y].hCost = 0.0;
	fullMap[x][y].ParentPos.x = x;
	fullMap[x][y].ParentPos.y = y;

	vector<PathNode> openList;

	openList.emplace_back(fullMap[x][y]);

	bool destFound = false;

	while (openList.size() > 0 && openList.size() < (SCR_W / MAXSTEP) * (SCR_H / MAXSTEP))
	{
		
		PathNode node;
		do
		{
			if (openList.size() == 0)
			{
				break;
			}
			float temp = FLT_MAX;
			vector<PathNode>::iterator itNode;
			for (vector<PathNode>::iterator it = openList.begin(); it != openList.end(); it = next(it))
			{
				PathNode n = *it;
				if (n.fCost < temp)
				{
					temp = n.fCost;
					itNode = it;
				}
			}
			node = *itNode;
			openList.erase(itNode);
		} while (!IsNodeValid(node.pos.x, node.pos.y));

		x = node.pos.x;
		y = node.pos.y;
		closedList[x][y] = true;

		for (int newX = -1; newX <= 1; newX++)
		{
			for (int newY = -1; newY<= 1; newY++)
			{
				double gnew, hnew, fnew;
				if (IsNodeValid(x + newX, y + newY))
				{
					if (isDestNode(x + newX , y + newY, dest))
					{
						fullMap[x + newX][y + newY ].ParentPos.x = x;
						fullMap[x + newX][y + newY ].ParentPos.y = y;
						destFound = true;
						return makePath(fullMap, dest);
					}
					else if (!closedList[x + newX][y + newY])
					{
						gnew = node.gCost + 1.0f;
						hnew = calculateH(x + newX , y + newY , dest);
						fnew = gnew + hnew;

						if (fullMap[x + newX][y  + newY].fCost == FLT_MAX || fullMap[x  + newX ][y  + newY].fCost > fnew)
						{
							fullMap[x + newX ][y + newY ].fCost = fnew;
							fullMap[x + newX ][y + newY ].gCost = gnew;
							fullMap[x + newX ][y + newY ].hCost = hnew;
							fullMap[x + newX ][y + newY ].ParentPos.x = x;
							fullMap[x + newX ][y + newY ].ParentPos.y = y;
							openList.emplace_back(fullMap[x + newX ][y + newY]);
						}
					}
				}
			}
		}

		
	}
	if (!destFound)
	{
		std::cout << "Destination not Found " << std::endl;
		return empty;
	}
}


/// <summary>
/// ****************************************** MAKE PATH FUNCTION ************************************************	
/// </summary>
vector<PathNode> TestBotBehaviourComponent::makePath(array<array<PathNode, (SCR_H / MAXSTEP)>, (SCR_W / MAXSTEP)> t_map, PathNode t_dest)
{
	try {
		cout << "Found Path" << std::endl;
		int x = t_dest.pos.x;
		int y = t_dest.pos.y;

		stack<PathNode> path;
		vector<PathNode> usablePath;

		while (!(t_map[x][y].ParentPos.x == x && t_map[x][y].ParentPos.y == y) && t_map[x][y].pos.x != -1 && t_map[x][y].pos.y != -1)
		{
			path.push(t_map[x][y]);
			int tempX = t_map[x][y].ParentPos.x;
			int tempY = t_map[x][y].ParentPos.y;
			x = tempX;
			y = tempY;
		}
		path.push(t_map[x][y]);

		while (!path.empty())
		{
			PathNode top = path.top();
			path.pop();
			usablePath.emplace_back(top);

		}
		return usablePath;
	}
	catch(const exception& e){
		std::cout << e.what() << std::endl;
	}
}

/// <summary>
/// *********************************************** CREATE NODE FROM OBJECT *******************************************
/// </summary>
/// <param name="t_struct"></param>
/// <returns></returns>
PathNode* TestBotBehaviourComponent::objectToNode(GoalStruct t_struct)
{
	int objX = t_struct.position.x;
	int objY = t_struct.position.y;

	PathNode* dest = new PathNode;

	for (int x = 0; x < SCR_W / MAXSTEP; x++)
	{
		for (int y = 0; y< SCR_H/ MAXSTEP; y++)
		{
			if (objX >= x* MAXSTEP && objX <= ((x * MAXSTEP )+ MAXSTEP) && objY >= y * MAXSTEP && objY <= ((y * MAXSTEP )+ MAXSTEP))
			{
				dest->pos.x = x;
				dest->pos.y = y;
			}
		}
	}
	return dest;
}

/// <summary>
/// ********************************************** SETUP STARTING NODE ****************************************************
/// </summary>
/// <returns></returns>
PathNode* TestBotBehaviourComponent::setStartNode()
{
	PositionComponent* posComp = dynamic_cast<PositionComponent*>(m_entity.getComponent(Types::Position));
	PathNode* start = new PathNode;

	for (int x = 0; x < SCR_W / MAXSTEP; x++)
	{
		for (int y = 0; y < SCR_H / MAXSTEP; y++)
		{
			if (posComp->getPositionX()>= x * MAXSTEP && posComp->getPositionX() <= (x * MAXSTEP + MAXSTEP) && posComp->getPositionY() >= y * MAXSTEP && posComp->getPositionY() <= (y * MAXSTEP + MAXSTEP))
			{
				start->pos.x = x;
				start->pos.y = y;
			}
		}
	}

	return start;
}

