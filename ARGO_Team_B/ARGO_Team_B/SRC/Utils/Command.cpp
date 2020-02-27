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

void MacroCommand::add(Command *t_c)
{
	m_commands->erase((m_commands->begin() + m_CommandsEnd), m_commands->end());
	m_commands->insert(m_commands->begin() + (m_CommandsEnd), t_c);
	m_CommandsEnd++;
}

void MacroCommand::remove(Command *t_c)
{
	m_commands->erase(std::find(m_commands->begin(), m_commands->end(), t_c), m_commands->end());
}

void MacroCommand::execute(Entity &t_e)
{
	for (int i = 0; i < m_commands->size(); i++)
	{
		Command *c = m_commands->at(i);
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

void WalkUpCommand::execute(Entity &t_gameObject)
{

	PositionComponent *posComp = dynamic_cast<PositionComponent *>(t_gameObject.getComponent(Types::Position));
	AnimatedSpriteComponent *anim = dynamic_cast<AnimatedSpriteComponent *>(t_gameObject.getComponent(Types::AnimatedSprite));

	//if (posComp->getPositionY() > 30) {
	posComp->moveUp();

	CollisionComponent* playerComp = dynamic_cast<CollisionComponent*>(t_gameObject.getComponent(Types::Collider));
	playerComp->updateCollider(t_gameObject, posComp->getangle());

	//}
	if (anim->getPrevious()->m_type != States::Walking)
	{
		anim->setCurrent(new WalkingState);
	}
}

/// <summary>
/// ------------------------- Walk Down Execute -----------------------------------
/// </summary>
void WalkDownCommand::execute(Entity& t_gameObject)
{
	PositionComponent* posComp = dynamic_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));
	AnimatedSpriteComponent* anim = dynamic_cast<AnimatedSpriteComponent*>(t_gameObject.getComponent(Types::AnimatedSprite));


	posComp->moveDown();
	CollisionComponent* playerComp = dynamic_cast<CollisionComponent*>(t_gameObject.getComponent(Types::Collider));
	playerComp->updateCollider(t_gameObject, posComp->getangle());
	
	if (anim->getPrevious()->m_type != States::Walking)
	{
		anim->setCurrent(new WalkingState);
	}

}

/// <summary>
/// ------------------------- Walk Left Execute -----------------------------------
/// </summary>
void WalkLeftCommand::execute(Entity &t_gameObject)
{
	PositionComponent *posComp = dynamic_cast<PositionComponent *>(t_gameObject.getComponent(Types::Position));
	AnimatedSpriteComponent *anim = dynamic_cast<AnimatedSpriteComponent *>(t_gameObject.getComponent(Types::AnimatedSprite));

	if (posComp->getPositionX() > 30)
	{
		//anim->setPrevious(anim->getCurrent());
		posComp->moveLeft();
		CollisionComponent* playerComp = dynamic_cast<CollisionComponent*>(t_gameObject.getComponent(Types::Collider));
		playerComp->updateCollider(t_gameObject, posComp->getangle());

		if (anim->getPrevious()->m_type != States::Walking)
		{
			anim->setCurrent(new WalkingState);
		}
	}
}

/// <summary>
/// ------------------------- Walk Right Execute -----------------------------------
/// </summary>
void WalkRightCommand::execute(Entity &t_gameObject)
{
	PositionComponent *posComp = dynamic_cast<PositionComponent *>(t_gameObject.getComponent(Types::Position));
	AnimatedSpriteComponent *anim = dynamic_cast<AnimatedSpriteComponent *>(t_gameObject.getComponent(Types::AnimatedSprite));

	if (posComp->getPositionX() < SCR_W - 90)
	{
		//anim->setPrevious(anim->getCurrent());
		posComp->moveRight();

		CollisionComponent* playerComp = dynamic_cast<CollisionComponent*>(t_gameObject.getComponent(Types::Collider));
		playerComp->updateCollider(t_gameObject, posComp->getangle());

		if (anim->getPrevious()->m_type != States::Walking)
		{
			anim->setCurrent(new WalkingState);
		}
	}
}

/// <summary>
/// ------------------------- Interact Execute -----------------------------------
/// </summary>
void InteractCommand::execute(Entity &t_gameObject)
{
	AnimatedSpriteComponent *anim = dynamic_cast<AnimatedSpriteComponent *>(t_gameObject.getComponent(Types::AnimatedSprite));
	PlayerComponent *playerComp = dynamic_cast<PlayerComponent *>(t_gameObject.getComponent(Types::Player));
	anim->setPrevious(anim->getCurrent());

	playerComp->setSwipeCooldown(0.5f);
	playerComp->setInteract(true);

	if (anim->getPrevious()->m_type != States::Interact)
	{
		anim->setCurrent(new InteractState);
	}
	playerComp->setInteract(true);
}
