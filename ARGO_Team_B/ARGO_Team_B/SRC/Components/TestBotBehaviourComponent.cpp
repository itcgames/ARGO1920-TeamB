#include "TestBotBehaviourComponent.h"

TestBotBehaviourComponent::TestBotBehaviourComponent(Entity& t_gameObject) :
	m_entity{ t_gameObject },
	wander("WanderMap",99) ,
	findCheese("hunt for cheese", 99) ,
	moveToCheese("move to Cheese", 99), 
	CollectCheese("pick Up Cheese", 100), 
	findButton("search for Button", 99),
	moveToButton("move to button", 99),
	findBomb("search for bomb", 99),
	moveToBomb("move to bomb", 100), 
	collectBomb("pick up bomb", 100), 
	wanderWithBomb("wandering with bomb", 100), 
	findPlayerInRange("look for player", 99),
	searchForPlayer("look for player", 99),
	chasePlayer("Move to player", 99),
	placebomb("drop the bomb", 100), 
	fleeBomb("getaway", 99)
{
	m_behaviorTree.setRootChild(&m_selector[0]);
	m_selector[0].addChildren({ &m_sequence[0],&m_sequence[1], &m_sequence[2] });
	m_sequence[0].addChildren({ &moveToCheese, &CollectCheese,&m_selector[0] });

	m_sequence[1].addChildren({ &moveToButton, &wander });
	m_sequence[2].addChildren({ &moveToBomb, &collectBomb,&m_selector[1] });

	m_selector[1].addChildren({ &m_sequence[3], &m_sequence[4] });
	
	m_sequence[3].addChildren({ &searchForPlayer });
	m_sequence[4].addChildren({ &placebomb, &fleeBomb, &m_selector[0] });

	if (m_behaviorTree.run())
	{
		std::cout << "Behaviour tree run successful";
	}
	else
	{
		std::cout << "Behaviour tree failed";
	}
	
}

TestBotBehaviourComponent::~TestBotBehaviourComponent()
{
}

void TestBotBehaviourComponent::update()
{
	if (m_behaviorTree.run())
	{
		std::cout << "Behaviour tree run successful";
	}
	else
	{
		std::cout << "Behaviour tree failed";
	}

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

