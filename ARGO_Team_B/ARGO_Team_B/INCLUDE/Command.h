#ifndef COMMAND_H
#define COMMAND_H

#include "Entity.h"
#include "PositionComponent.h"
class Command
{
public :
	virtual ~Command() {};
	virtual void execute(Entity & t_gameObject) = 0;

};

class WalkUpCommand : public Command {
public:
	virtual void execute(Entity & t_gameObject)
	{
		PositionComponent* posComp = dynamic_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));
		posComp->moveUp();

	}
};

class WalkDownCommand : public Command {
public:
	virtual void execute(Entity & t_gameObject)
	{
		PositionComponent* posComp = dynamic_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));
		posComp->moveDown();

	}
};

class WalkLeftCommand : public Command {
public:
	virtual void execute(Entity & t_gameObject)
	{
		PositionComponent* posComp = dynamic_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));
		posComp->moveLeft();

	}
};

class WalkRightCommand : public Command {
public:
	virtual void execute(Entity & t_gameObject)
	{
		PositionComponent* posComp = dynamic_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));
		posComp->moveRight();

	}
};

#endif
