#include "ControlComponent.h"

ControlComponent::ControlComponent(Entity & t_gameObject) :
	m_entity(t_gameObject) 
{
	m_compNum = s_controlID++;
	m_controller = new Xbox360Controller(m_compNum);
}

ControlComponent::~ControlComponent()
{
}

void ControlComponent::handleInput(StateMachineSystem& t_stateSystem)
{
	PositionComponent* posComp = dynamic_cast<PositionComponent*>(m_entity.getComponent(Types::Position));
	PlayerComponent* playerComp = dynamic_cast<PlayerComponent*>(m_entity.getComponent(Types::Player));

	//reset interact 
	playerComp->setInteract(false);

	m_controller->checkButton();
	if (playerComp->getMoveable() && !playerComp->getDizzy()) {
		posComp->setPreviousePos();

		if (m_controller->m_currentState.A && playerComp->getSwipeCooldown() <= 0.0f) {
			controlInteract(playerComp, t_stateSystem);
		}

		if (m_controller->m_currentState.DpadUp || m_controller->m_currentState.LeftThumbStick.y < -m_controller->dpadThreshold) {
			controlUp(posComp, t_stateSystem);
		}
		else if (m_controller->m_currentState.DpadLeft || m_controller->m_currentState.LeftThumbStick.x < -m_controller->dpadThreshold) {
			controlLeft(posComp, t_stateSystem);

		}
		else if (m_controller->m_currentState.DpadRight || m_controller->m_currentState.LeftThumbStick.x > m_controller->dpadThreshold) {
			controlRight(posComp, t_stateSystem);
		}
		else if (m_controller->m_currentState.DpadDown || m_controller->m_currentState.LeftThumbStick.y > m_controller->dpadThreshold) {
			controlDown(posComp, t_stateSystem);
		}
	}
	else if (!playerComp->getMoveable()) {
		posComp->backToPreviousePos();
		playerComp->setMoveable(true);
	}

	if (m_controller->m_currentState.X)
	{
		m_commandSquence->execute(m_entity);
		m_commandSquence->clear();
	}
}

void ControlComponent::controlInteract(PlayerComponent* t_player, StateMachineSystem& t_stateSystem)
{
	p_interact = new InteractCommand();
	p_interact->execute(m_entity);
	m_commandSquence->add(p_interact);
	SDL_HapticRumblePlay(m_controller->m_controllerHaptic, 0.25, 200);
	t_player->setSwipeCooldown(0.5f);
	t_player->setInteract(true);
	t_stateSystem.setCurrent(States::Interact);
}

void ControlComponent::controlUp(PositionComponent* t_pos, StateMachineSystem& t_stateSystem)
{
	p_walkUp = new WalkUpCommand();
	p_walkUp->execute(m_entity);
	m_commandSquence->add(p_walkUp);
	float length = sqrt((m_controller->m_currentState.LeftThumbStick.x * m_controller->m_currentState.LeftThumbStick.x) + (m_controller->m_currentState.LeftThumbStick.y * m_controller->m_currentState.LeftThumbStick.y));
	double angle = atan2(m_controller->m_currentState.LeftThumbStick.x / length, (m_controller->m_currentState.LeftThumbStick.y / length) * -1);
	t_pos->setangle((angle * (180 / 3.14)));
	t_stateSystem.setCurrent(States::Walking);
}

void ControlComponent::controlDown(PositionComponent* t_pos, StateMachineSystem& t_stateSystem)
{
	p_walkDown = new WalkDownCommand();
	p_walkDown->execute(m_entity);
	m_commandSquence->add(p_walkDown);
	float length = sqrt((m_controller->m_currentState.LeftThumbStick.x * m_controller->m_currentState.LeftThumbStick.x) + (m_controller->m_currentState.LeftThumbStick.y * m_controller->m_currentState.LeftThumbStick.y));
	double angle = atan2(m_controller->m_currentState.LeftThumbStick.x / length, (m_controller->m_currentState.LeftThumbStick.y / length) * -1);
	t_pos->setangle((angle * (180 / 3.14)));
	t_stateSystem.setCurrent(States::Walking);
}

void ControlComponent::controlLeft(PositionComponent* t_pos, StateMachineSystem& t_stateSystem)
{
	p_walkLeft = new WalkLeftCommand();
	p_walkLeft->execute(m_entity);

	m_commandSquence->add(p_walkLeft);

	float length = sqrt((m_controller->m_currentState.LeftThumbStick.x * m_controller->m_currentState.LeftThumbStick.x) + (m_controller->m_currentState.LeftThumbStick.y * m_controller->m_currentState.LeftThumbStick.y));
	double angle = atan2(m_controller->m_currentState.LeftThumbStick.x / length, (m_controller->m_currentState.LeftThumbStick.y / length) * -1);
	t_pos->setangle((angle * (180 / 3.14)));

	t_stateSystem.setCurrent(States::Walking);
}

void ControlComponent::controlRight(PositionComponent* t_pos , StateMachineSystem& t_stateSystem)
{
	p_walkRight = new WalkRightCommand();
	p_walkRight->execute(m_entity);
	m_commandSquence->add(p_walkRight);

	float length = sqrt((m_controller->m_currentState.LeftThumbStick.x * m_controller->m_currentState.LeftThumbStick.x) + (m_controller->m_currentState.LeftThumbStick.y * m_controller->m_currentState.LeftThumbStick.y));
	double angle = atan2(m_controller->m_currentState.LeftThumbStick.x / length, (m_controller->m_currentState.LeftThumbStick.y / length) * -1);
	t_pos->setangle((angle * (180 / 3.14)));

	t_stateSystem.setCurrent(States::Walking);
}

void ControlComponent::moveUp()
{
	RenderComponent* renderComp = dynamic_cast<RenderComponent*>(m_entity.getComponent(Types::Render));
	p_walkUp = new WalkUpCommand();
	p_walkUp->execute(m_entity);
}

void ControlComponent::moveLeft()
{
	RenderComponent* renderComp = dynamic_cast<RenderComponent*>(m_entity.getComponent(Types::Render));
	p_walkLeft = new WalkLeftCommand();
	p_walkLeft->execute(m_entity);
}

void ControlComponent::moveRight()
{
	RenderComponent* renderComp = dynamic_cast<RenderComponent*>(m_entity.getComponent(Types::Render));
	p_walkRight = new WalkRightCommand();
	p_walkRight->execute(m_entity);
}

void ControlComponent::moveDown()
{
	RenderComponent* renderComp = dynamic_cast<RenderComponent*>(m_entity.getComponent(Types::Render));
	p_walkDown = new WalkDownCommand();
	p_walkDown->execute(m_entity);
}

