#include "Command.h"

/// <summary>
/// -------------------------------- Macro Commands ---------------------------------------------
/// </summary>
MacroCommand::~MacroCommand()
{
	if (m_commands)
	{
		delete m_commands;
	}
}

void MacroCommand::add(Command* t_c)
{
	m_commands->erase((m_commands->begin() + m_CommandsEnd), m_commands->end());
	m_commands->insert(m_commands->begin() + (m_CommandsEnd), t_c);
	m_CommandsEnd++;
}	

void MacroCommand::remove(Command* t_c)
{
	m_commands->erase(std::find(m_commands->begin(), m_commands->end(), t_c), m_commands->end());
}

void MacroCommand::execute(Entity & t_e)
{
	for (int i = 0; i < m_commands->size(); i++)
	{
		Command* c = m_commands->at(i);
		c->execute(t_e);

	}

}

void MacroCommand::clear()
{
	m_commands->clear();
}

/// <summary>
/// ------------------------- Walk Up Execute -----------------------------------
/// </summary>

void WalkUpCommand::execute(Entity& t_gameObject)
{
	{
		PositionComponent* posComp = dynamic_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));

		if (t_gameObject.getId() == 0 || t_gameObject.getId() == 1) {
			//if (posComp->getPositionY() > 30) {
				posComp->moveUp();
				CollisionComponent* colComp = dynamic_cast<CollisionComponent*>(t_gameObject.getComponent(Types::Collider));
				colComp->updateCollider(t_gameObject);
			//}
		}
		else if (t_gameObject.getId() == 2 || t_gameObject.getId() == 3) {
			if (posComp->getPositionY() > SCR_H + 50) {
				posComp->moveUp();

			}
		}
	}
}


/// <summary>
/// ------------------------- Walk Down Execute -----------------------------------
/// </summary>
void WalkDownCommand::execute(Entity& t_gameObject)
{
	RenderComponent* renderComp = dynamic_cast<RenderComponent*>(t_gameObject.getComponent(Types::Render));
	PositionComponent* posComp = dynamic_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));

	if (t_gameObject.getId() == 2 || t_gameObject.getId() == 3) {
		//if (posComp->getPositionY() < SCR_H - 75) {
		posComp->moveDown();
		CollisionComponent* colComp = dynamic_cast<CollisionComponent*>(t_gameObject.getComponent(Types::Collider));
		colComp->updateCollider(t_gameObject);
		//}

	}
	else if (t_gameObject.getId() == 0 || t_gameObject.getId() == 1) {
		//if (posComp->getPositionY() < SCR_H - 45) {
		posComp->moveDown();
		CollisionComponent* colComp = dynamic_cast<CollisionComponent*>(t_gameObject.getComponent(Types::Collider));
		colComp->updateCollider(t_gameObject);
		//}
	}
}

/// <summary>
/// ------------------------- Walk Left Execute -----------------------------------
/// </summary>
void WalkLeftCommand::execute(Entity& t_gameObject)
{
	RenderComponent* renderComp = dynamic_cast<RenderComponent*>(t_gameObject.getComponent(Types::Render));
	PositionComponent* posComp = dynamic_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));

	if (posComp->getPositionX() > 30) {
		posComp->moveLeft();

	}
}

/// <summary>
/// ------------------------- Walk Right Execute -----------------------------------
/// </summary>
void WalkRightCommand::execute(Entity& t_gameObject)
{
	RenderComponent* renderComp = dynamic_cast<RenderComponent*>(t_gameObject.getComponent(Types::Render));
	PositionComponent* posComp = dynamic_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));
	

	if (posComp->getPositionX() < SCR_W - 90) {
		posComp->moveRight();

	}

}

/// <summary>
/// ------------------------- Interact Execute -----------------------------------
/// </summary>
void InteractCommand::execute(Entity& t_gameObject)
{
	PlayerComponent* playerComp = dynamic_cast<PlayerComponent*>(t_gameObject.getComponent(Types::Player));




	playerComp->setSwipeCooldown(0.5f);
	playerComp->setInteract(true);

	playerComp->setInteract(true);
}