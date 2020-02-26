#ifndef COMMAND_H
#define COMMAND_H

#include "Entity.h"
#include "PositionComponent.h"
#include "CollisionComponent.h"
#include "PlayerComponent.h"
#include "RenderComponent.h"
#include "AnimatedSpriteComponent.h"
#include <vector>

class Command
{
public:
	virtual ~Command() {};
	virtual void execute(Entity& t_gameObject) = 0;

};

class MacroCommand : public Command
{
public:
	MacroCommand() { m_commands = new std::vector<Command*>(); };

	virtual ~MacroCommand();
	virtual void add(Command* t_c);
	virtual void remove(Command* t_c);
	virtual void execute(Entity& t_e);
	virtual void clear();

private:
	int m_CommandsEnd{};
	std::vector<Command* >*  m_commands;

};

class WalkUpCommand : public Command {
public:
	virtual void execute(Entity& t_gameObject);
};

class WalkDownCommand : public Command {
public:
	virtual void execute(Entity& t_gameObject);
};

class WalkLeftCommand : public Command {
public:
	virtual void execute(Entity& t_gameObject);
};

class WalkRightCommand : public Command {
public:
	virtual void execute(Entity& t_gameObject);
};

class InteractCommand : public Command {
public:
	virtual void execute(Entity& t_gameObject);
};
#endif
