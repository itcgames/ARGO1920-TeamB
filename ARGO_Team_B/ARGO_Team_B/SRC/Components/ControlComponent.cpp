#include "ControlComponent.h"

ControlComponent::ControlComponent(Entity& t_gameObject, int controller):
	m_entity(t_gameObject)
{
	m_compNum = controller;
	m_controller = new Xbox360Controller(m_compNum);
}

ControlComponent::ControlComponent(Entity& t_gameObject) :
	m_entity(t_gameObject) 
{
	m_compNum = s_controlID++;
	m_controller = new Xbox360Controller(m_compNum);
}

ControlComponent::~ControlComponent()
{
}

void ControlComponent::handleInput(SDL_Renderer* t_renderer,std::vector<ParticleSystem*>&t_ps,float dt)
{
	PositionComponent* posComp = dynamic_cast<PositionComponent*>(m_entity.getComponent(Types::Position));
	PlayerComponent* playerComp = dynamic_cast<PlayerComponent*>(m_entity.getComponent(Types::Player));

	//reset interact 
	playerComp->setInteract(false);
	
	m_controller->checkButton();
	if (playerComp->getMoveable() && !playerComp->getDizzy()) {
		posComp->setPreviousePos();

		if (m_controller->m_currentState.A && playerComp->getSwipeCooldown() <= 0.0f) {
			controlInteract(playerComp);
		}

		if (m_controller->m_currentState.LeftThumbStick.y < -m_controller->dpadThreshold) {
			controlUp(posComp);
			t_ps.push_back((new ParticleSystem(10, posComp->getPositionX()+3, posComp->getPositionY() + 30, t_renderer, ParticleType::Dust)));
		}
		else if (m_controller->m_currentState.LeftThumbStick.y > m_controller->dpadThreshold) {
			controlDown(posComp);
			t_ps.push_back((new ParticleSystem(10, posComp->getPositionX() + 2, posComp->getPositionY() + 1, t_renderer, ParticleType::Dust)));
		}
		else {
			posComp->slowDownY();
		}

		if (m_controller->m_currentState.LeftThumbStick.x < -m_controller->dpadThreshold) {
			controlLeft(posComp);
			t_ps.push_back((new ParticleSystem(10, posComp->getPositionX()+10, posComp->getPositionY()+17, t_renderer, ParticleType::Dust)));
		}
		else if (m_controller->m_currentState.LeftThumbStick.x > m_controller->dpadThreshold) {
			controlRight(posComp);
			t_ps.push_back((new ParticleSystem(10, posComp->getPositionX() -10, posComp->getPositionY()+18, t_renderer, ParticleType::Dust)));
		}
		else {
			posComp->slowDownX();
		}

		if (m_controller->m_currentState.LeftThumbStick.x < m_controller->dpadThreshold &&
			m_controller->m_currentState.LeftThumbStick.x > -m_controller->dpadThreshold &&
			m_controller->m_currentState.LeftThumbStick.y < m_controller->dpadThreshold  &&
			m_controller->m_currentState.LeftThumbStick.y > -m_controller->dpadThreshold) {
			posComp->setangle(0);
		}

	}
	else if (!playerComp->getMoveable()) {
		posComp->backToPreviousePos();
		playerComp->setMoveable(true);
	}

	posComp->movementUpdate(dt);
}

void ControlComponent::controlInteract(PlayerComponent* t_player)
{	
	p_interact = new InteractCommand();
	p_interact->execute(m_entity);
	m_commandSquence->add(p_interact);
	SDL_HapticRumblePlay(m_controller->m_controllerHaptic, 0.25, 200);
	t_player->setSwipeCooldown(0.5f);
	t_player->setInteract(true);
}

void ControlComponent::controlUp(PositionComponent* t_pos)
{
	p_walkUp = new WalkUpCommand();
	p_walkUp->execute(m_entity);
	m_commandSquence->add(p_walkUp);
	float length = sqrt((m_controller->m_currentState.LeftThumbStick.x * m_controller->m_currentState.LeftThumbStick.x) + (m_controller->m_currentState.LeftThumbStick.y * m_controller->m_currentState.LeftThumbStick.y));
	double angle = atan2(m_controller->m_currentState.LeftThumbStick.x / length, (m_controller->m_currentState.LeftThumbStick.y / length) * -1);
	t_pos->setangle((angle * (180 / 3.14)));
}

void ControlComponent::controlDown(PositionComponent* t_pos)
{
	p_walkDown = new WalkDownCommand();
	p_walkDown->execute(m_entity);
	m_commandSquence->add(p_walkDown);
	float length = sqrt((m_controller->m_currentState.LeftThumbStick.x * m_controller->m_currentState.LeftThumbStick.x) + (m_controller->m_currentState.LeftThumbStick.y * m_controller->m_currentState.LeftThumbStick.y));
	double angle = atan2(m_controller->m_currentState.LeftThumbStick.x / length, (m_controller->m_currentState.LeftThumbStick.y / length) * -1);
	t_pos->setangle((angle * (180 / 3.14)));
}

void ControlComponent::controlLeft(PositionComponent* t_pos)
{
	p_walkLeft = new WalkLeftCommand();
	p_walkLeft->execute(m_entity);
	m_commandSquence->add(p_walkLeft);
	float length = sqrt((m_controller->m_currentState.LeftThumbStick.x * m_controller->m_currentState.LeftThumbStick.x) + (m_controller->m_currentState.LeftThumbStick.y * m_controller->m_currentState.LeftThumbStick.y));
	double angle = atan2(m_controller->m_currentState.LeftThumbStick.x / length, (m_controller->m_currentState.LeftThumbStick.y / length) * -1);
	t_pos->setangle((angle * (180 / 3.14)));
}

void ControlComponent::controlRight(PositionComponent* t_pos)
{
	p_walkRight = new WalkRightCommand();
	p_walkRight->execute(m_entity);
	m_commandSquence->add(p_walkRight);
	float length = sqrt((m_controller->m_currentState.LeftThumbStick.x * m_controller->m_currentState.LeftThumbStick.x) + (m_controller->m_currentState.LeftThumbStick.y * m_controller->m_currentState.LeftThumbStick.y));
	double angle = atan2(m_controller->m_currentState.LeftThumbStick.x / length, (m_controller->m_currentState.LeftThumbStick.y / length) * -1);
	t_pos->setangle((angle * (180 / 3.14)));
}
