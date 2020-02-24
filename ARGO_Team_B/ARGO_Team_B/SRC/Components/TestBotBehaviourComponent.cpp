#include "TestBotBehaviourComponent.h"

TestBotBehaviourComponent::TestBotBehaviourComponent(Entity& t_gameObject) :
	m_entity{ t_gameObject }
{
}

TestBotBehaviourComponent::~TestBotBehaviourComponent()
{
}

void TestBotBehaviourComponent::update()
{
	PlayerComponent* playerComp = dynamic_cast<PlayerComponent*>(m_entity.getComponent(Types::Player));
	PositionComponent* posComp = dynamic_cast<PositionComponent*>(m_entity.getComponent(Types::Position));
	ControlComponent *control = dynamic_cast<ControlComponent*>(m_entity.getComponent(Types::Control));
	//reset interact 
	playerComp->setInteract(false);
	if (playerComp->getMoveable() && !playerComp->getDizzy()) {

		if (control != nullptr)
		{
			//if (i == 0) {

				//posComp->moveLeft();
				//posComp->moveRight();

				control->controlLeft(posComp);
				//control->controlUp(posComp);
				control->controlRight(posComp);
				//control->controlDown(posComp);

				//i++;
			// }
		}
		else if (!playerComp->getMoveable()) {
			posComp->backToPreviousePos();
			playerComp->setMoveable(true);
		}
	}
}

