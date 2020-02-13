#ifndef COMMAND_H
#define COMMAND_H

#include "Entity.h"
#include "PositionComponent.h"
#include "CollisionComponent.h"
#include "PlayerComponent.h"
#include "RenderComponent.h"
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

		if (t_gameObject.getId() == 0 || t_gameObject.getId() == 1) {
			if (posComp->getPositionY() > 40) {
				posComp->moveUp();

			}
		}
		else if (t_gameObject.getId() == 2 || t_gameObject.getId() == 3) {
			if (posComp->getPositionY() > SCR_H / 2 + 50) {
				posComp->moveUp();

			}
		}
	}
};

class WalkDownCommand : public Command {
public:
	virtual void execute(Entity& t_gameObject)
	{
		RenderComponent* renderComp = dynamic_cast<RenderComponent*>(t_gameObject.getComponent(Types::Render));
		PositionComponent* posComp = dynamic_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));

		if (t_gameObject.getId() == 2 || t_gameObject.getId() == 3) {
			if (posComp->getPositionY() < SCR_H - 75) {
				posComp->moveDown();

			}
		}
		else if (t_gameObject.getId() == 0 || t_gameObject.getId() == 1) {
			if (posComp->getPositionY() < SCR_H / 2 - 45) {
				posComp->moveDown();

			}
		}
	}
};

class WalkLeftCommand : public Command {
public:
	virtual void execute(Entity& t_gameObject)
	{
		RenderComponent* renderComp = dynamic_cast<RenderComponent*>(t_gameObject.getComponent(Types::Render));
		PositionComponent* posComp = dynamic_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));

		if (posComp->getPositionX() > 30) {
			posComp->moveLeft();

		}
	}
};

class WalkRightCommand : public Command {
public:
	virtual void execute(Entity& t_gameObject)
	{
		RenderComponent* renderComp = dynamic_cast<RenderComponent*>(t_gameObject.getComponent(Types::Render));
		PositionComponent* posComp = dynamic_cast<PositionComponent*>(t_gameObject.getComponent(Types::Position));


		if (posComp->getPositionX() < SCR_W - 90) {
			posComp->moveRight();
		}

	}
};

class InteractCommand : public Command {
public:
	virtual void execute(Entity& t_gameObject)
	{
		PlayerComponent* playerComp = dynamic_cast<PlayerComponent*>(t_gameObject.getComponent(Types::Player));

		playerComp->setInteract(true);
	}
};
#endif
