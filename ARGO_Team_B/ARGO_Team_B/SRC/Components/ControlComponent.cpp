#include "ControlComponent.h"

ControlComponent::ControlComponent(Entity & t_gameObject):
	m_entity(t_gameObject),
	m_moving(MovingState::Idle)
{
	m_compNum = s_controlID++;
	m_controller = new Xbox360Controller(m_compNum);
}

ControlComponent::~ControlComponent()
{
}

//void ControlComponent::update(float dt)
//{
//	PositionComponent* posComp =
//		dynamic_cast<PositionComponent*>(m_entity.getComponent(Types::Position));
//	if (posComp != nullptr)
//	{
//		switch (m_moving) {
//		case MovingState::Up:
//			if (m_entity.getId() == 0 || m_entity.getId() == 1) {
//				if (posComp->getPositionY() > 40) {
//					moveUp();
//				}
//			}
//			else if (m_entity.getId() == 2 || m_entity.getId() == 3) {
//				if (posComp->getPositionY() > SCR_H / 2 + 50) {
//					moveUp();
//				}
//			}
//			break;
//		case MovingState::Down:
//			if (m_entity.getId() == 2 || m_entity.getId() == 3) {
//				if (posComp->getPositionY() < SCR_H - 75) {
//					moveDown();
//				}
//			}
//			else if (m_entity.getId() == 0 || m_entity.getId() == 1) {
//				if (posComp->getPositionY() < SCR_H / 2 - 45) {
//					moveDown();
//				}
//			}
//			break;
//		case MovingState::Left:
//			if (posComp->getPositionX() > 30) {
//				moveLeft();
//			}
//			break;
//		case MovingState::Right:
//			if (posComp->getPositionX() < SCR_W - 90) {
//				moveRight();
//			}
//			break;
//		case MovingState::Idle:
//			if (posComp->getVeloX() > 0 || posComp->getVeloX() < 0) {
//				posComp->setVelo(posComp->getVeloX() * 0.90f, posComp->getVeloY());
//			}
//			else {
//				posComp->setVelo(0, posComp->getVeloY());
//			}
//
//			if (posComp->getVeloY() > 0 || posComp->getVeloY() < 0) {
//				posComp->setVelo(posComp->getVeloX(), posComp->getVeloY() * 0.90f);
//			}
//			else {
//				posComp->setVelo(posComp->getVeloX(), 0 );
//			}
//			break;
//		}
//		posComp->setPosition(posComp->getPositionX() + posComp->getVeloX() / dt, posComp->getPositionY() + posComp->getVeloY() / dt);
//	}
//}

void ControlComponent::handleInput()
{
	PositionComponent* posComp = dynamic_cast<PositionComponent*>(m_entity.getComponent(Types::Position));

	PlayerComponent* playerComp = dynamic_cast<PlayerComponent*>(m_entity.getComponent(Types::Player));

	//reset interact 
	playerComp->setInteract(false);

	m_controller->checkButton();
	if (playerComp->getMoveable() && !playerComp->getDizzy()) {
		posComp->setPreviousePos();

		if (m_controller->m_currentState.A && playerComp->getSwipeCooldown() <= 0.0f) {
			p_interact = new InteractCommand();
			p_interact->execute(m_entity);

			playerComp->setSwipeCooldown(0.5f);
			playerComp->setInteract(true);
		}

		if (m_controller->m_currentState.DpadUp || m_controller->m_currentState.LeftThumbStick.y < -m_controller->dpadThreshold) {
			p_walkUp = new WalkUpCommand();
			p_walkUp->execute(m_entity);
			//renderComp->setAngle(270);
		}

		if (m_controller->m_currentState.DpadLeft || m_controller->m_currentState.LeftThumbStick.x < -m_controller->dpadThreshold) {
			p_walkLeft = new WalkLeftCommand();
			p_walkLeft->execute(m_entity);
			//renderComp->setAngle(180);
		}
		//else {
		//	m_moving = MovingState::Idle;
		//}

		if (m_controller->m_currentState.DpadRight || m_controller->m_currentState.LeftThumbStick.x > m_controller->dpadThreshold) {
			p_walkRight = new WalkRightCommand();
			p_walkRight->execute(m_entity);
			//renderComp->setAngle(0);
		}

		if (m_controller->m_currentState.DpadDown || m_controller->m_currentState.LeftThumbStick.y > m_controller->dpadThreshold) {
			p_walkDown = new WalkDownCommand();
			p_walkDown->execute(m_entity);
			//renderComp->setAngle(90);
		}
	}
	else if (!playerComp->getMoveable()) {
		posComp->backToPreviousePos();
		playerComp->setMoveable(true);
	}
	/*m_controller->m_currentState.DpadUp = false;
	m_controller->m_currentState.DpadDown= false;
	m_controller->m_currentState.DpadLeft = false;
	m_controller->m_currentState.DpadRight = false;
	m_controller->m_currentState.LeftThumbStick.x = 0;
	m_controller->m_currentState.LeftThumbStick.y = 0;*/
}

void ControlComponent::moveUp()
{
	RenderComponent* renderComp = dynamic_cast<RenderComponent*>(m_entity.getComponent(Types::Render));
	p_walkUp = new WalkUpCommand();
	p_walkUp->execute(m_entity);
	renderComp->setAngle(270);
}

void ControlComponent::moveLeft()
{
	RenderComponent* renderComp = dynamic_cast<RenderComponent*>(m_entity.getComponent(Types::Render));
	p_walkLeft = new WalkLeftCommand();
	p_walkLeft->execute(m_entity);
	renderComp->setAngle(180);
}

void ControlComponent::moveRight()
{
	RenderComponent* renderComp = dynamic_cast<RenderComponent*>(m_entity.getComponent(Types::Render));
	p_walkRight = new WalkRightCommand();
	p_walkRight->execute(m_entity);
	renderComp->setAngle(0);
}

void ControlComponent::moveDown()
{
	RenderComponent* renderComp = dynamic_cast<RenderComponent*>(m_entity.getComponent(Types::Render));
	p_walkDown = new WalkDownCommand();
	p_walkDown->execute(m_entity);
	renderComp->setAngle(90);
}

