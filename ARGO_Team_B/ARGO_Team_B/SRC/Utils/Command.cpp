#include "Command.h"
#include "IdleState.h"
#include "WalkingState.h"
#include "InteractState.h"
#include "StunnedState.h"


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
		AnimatedSpriteComponent* anim = dynamic_cast<AnimatedSpriteComponent*>(t_gameObject.getComponent(Types::AnimatedSprite));
		
		if (t_gameObject.getId() == 0 || t_gameObject.getId() == 1) {
			//if (posComp->getPositionY() > 30) {
				posComp->moveUp();
				CollisionComponent* colComp = dynamic_cast<CollisionComponent*>(t_gameObject.getComponent(Types::Collider));
				colComp->updateCollider(t_gameObject);
			//}
				if (anim->getPrevious()->m_type != States::Walking)
				{
					anim->setCurrent(new WalkingState);
				}
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
	PositionComponent* posComp = dynamic_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));
	AnimatedSpriteComponent* anim = dynamic_cast<AnimatedSpriteComponent*>(t_gameObject.getComponent(Types::AnimatedSprite));

	if (t_gameObject.getId() == 2 || t_gameObject.getId() == 3) {
		//anim->setPrevious(anim->getCurrent());
		//if (posComp->getPositionY() < SCR_H - 75) {
		posComp->moveDown();
		CollisionComponent* colComp = dynamic_cast<CollisionComponent*>(t_gameObject.getComponent(Types::Collider));
		colComp->updateCollider(t_gameObject);
		//}
		if (anim->getPrevious()->m_type != States::Walking)
		{
			anim->setCurrent(new WalkingState);
		}
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
	PositionComponent* posComp = dynamic_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));
	AnimatedSpriteComponent* anim = dynamic_cast<AnimatedSpriteComponent*>(t_gameObject.getComponent(Types::AnimatedSprite));

	if (posComp->getPositionX() > 30) {
		//anim->setPrevious(anim->getCurrent());
		posComp->moveLeft();
		if (anim->getPrevious()->m_type != States::Walking)
		{
			anim->setCurrent(new WalkingState);
		}
	}
}

/// <summary>
/// ------------------------- Walk Right Execute -----------------------------------
/// </summary>
void WalkRightCommand::execute(Entity& t_gameObject)
{
	PositionComponent* posComp = dynamic_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));
	AnimatedSpriteComponent* anim = dynamic_cast<AnimatedSpriteComponent*>(t_gameObject.getComponent(Types::AnimatedSprite));

	if (posComp->getPositionX() < SCR_W - 90) {
		//anim->setPrevious(anim->getCurrent());
		posComp->moveRight();

		if (anim->getPrevious()->m_type != States::Walking)
		{
			anim->setCurrent(new WalkingState);
		}
	}
}

/// <summary>
/// ------------------------- Interact Execute -----------------------------------
/// </summary>
void InteractCommand::execute(Entity& t_gameObject)
{
	AnimatedSpriteComponent* anim = dynamic_cast<AnimatedSpriteComponent*>(t_gameObject.getComponent(Types::AnimatedSprite));
	PlayerComponent* playerComp = dynamic_cast<PlayerComponent*>(t_gameObject.getComponent(Types::Player));
	//anim->setPrevious(anim->getCurrent());

	playerComp->setSwipeCooldown(0.5f);
	playerComp->setInteract(true);

	if (anim->getPrevious()->m_type != States::Interact)
	{
		anim->setCurrent(new InteractState);
	}
	playerComp->setInteract(true);
}