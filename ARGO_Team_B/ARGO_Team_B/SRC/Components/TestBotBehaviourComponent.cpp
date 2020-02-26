#include "TestBotBehaviourComponent.h"

TestBotBehaviourComponent::TestBotBehaviourComponent(std::vector<Entity*>& t_entities, Entity& t_gameObject) :
m_entity(t_gameObject)
{
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
	}
	m_TargetCheese = FindClosest(m_cheeses);
}

TestBotBehaviourComponent::TestBotBehaviourComponent(Entity& t_gameObject) :
	m_entity{ t_gameObject }	
{
		
}

TestBotBehaviourComponent::~TestBotBehaviourComponent()
{
}

void TestBotBehaviourComponent::update()
{
	wander();

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

void TestBotBehaviourComponent::moveToGoal(GoalStruct* t_goal)
{
	PositionComponent* posComp =  dynamic_cast<PositionComponent*>(m_entity.getComponent(Types::Position));


	float directionAngle = atan2( posComp->getPositionY() - t_goal->position.y, posComp->getPositionX()- t_goal->position.x) * (180/3.14);

	SDL_Point directionVector;
	directionVector.x = (t_goal->position.x + posComp->getPositionX()) / directionAngle;
	directionVector.y = (t_goal->position.y + posComp->getPositionY()) / directionAngle;


	posComp->setPosition(posComp->getPositionX() + directionVector.x, posComp->getPositionY() + directionVector.y);
	posComp->setangle(directionAngle);

}

GoalStruct* TestBotBehaviourComponent::FindClosest(std::vector<GoalStruct*> t_goals)
{
	GoalStruct* m_closest = nullptr;
	float shortest = t_goals[0]->distanceToPlayer;
	for (GoalStruct* goal : t_goals)
	{
		if (goal->distanceToPlayer < shortest && goal->isActive)
		{
			m_closest = goal;
		}
	}
	return m_closest;
}

