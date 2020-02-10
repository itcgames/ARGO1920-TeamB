#ifndef COMMAND_H
#define COMMAND_H

#include "Entity.h"
#include "PositionComponent.h"
#include "CollisionComponent.h"
#include "Globals.h"

class Command
{
public:
	virtual ~Command() {};
	virtual void execute(Entity& t_gameObject) = 0;

};

class WalkUpCommand : public Command {
public:
	virtual void execute(Entity& t_gameObject)
	{
		PositionComponent* posComp = dynamic_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));
		posComp->moveUp();

		CollisionComponent* colComp = dynamic_cast<CollisionComponent*>(t_gameObject.getComponent(Types::Collider));
		colComp->updateCollider(t_gameObject);
	}
};

class WalkDownCommand : public Command {
public:
	virtual void execute(Entity& t_gameObject)
	{
		PositionComponent* posComp = dynamic_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));
		if (posComp->getPositionY() > 30) {
			posComp->moveDown();
			CollisionComponent* colComp = dynamic_cast<CollisionComponent*>(t_gameObject.getComponent(Types::Collider));
			colComp->updateCollider(t_gameObject);
		}
	}
};

class WalkLeftCommand : public Command {
public:
	virtual void execute(Entity& t_gameObject)
	{
		PositionComponent* posComp = dynamic_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));
		if (posComp->getPositionX() > 30) {
			posComp->moveLeft();
			CollisionComponent* colComp = dynamic_cast<CollisionComponent*>(t_gameObject.getComponent(Types::Collider));
			colComp->updateCollider(t_gameObject);
		}
	}
};

class WalkRightCommand : public Command {
public:
	virtual void execute(Entity& t_gameObject)
	{
		PositionComponent* posComp = dynamic_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));
		if (posComp->getPositionX() < SCR_W - 90) {
			posComp->moveRight();
			CollisionComponent* colComp = dynamic_cast<CollisionComponent*>(t_gameObject.getComponent(Types::Collider));
			colComp->updateCollider(t_gameObject);
		}
	}
};

#endif
