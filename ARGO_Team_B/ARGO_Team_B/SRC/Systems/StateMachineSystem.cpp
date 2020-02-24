#include "StateMachineSystem.h"


StateMachineSystem::StateMachineSystem() :
	m_current{ new IdleState() }
{
	for (Entity& e : entities)
	{
		checkStates(m_current, &e);
	}
}

StateMachineSystem::~StateMachineSystem()
{
}

void StateMachineSystem::updateComponent(Component* c)
{
	for (Entity& e : entities)
	{
		if (e.getEntityType() == EntityType::Rat)
		{
			AnimatedSpriteComponent* animated = dynamic_cast<AnimatedSpriteComponent*>(e.getComponent(Types::AnimatedSprite));
			PositionComponent* pos = dynamic_cast<PositionComponent*>(e.getComponent(Types::Position));
			if (animated != nullptr)
			{
				checkStates(animated->getCurrent(), &e);
				animated->update();
				animated->render(pos->getPositionX(), pos->getPositionY(), pos->getangle());
			}
		}
	}
}


void StateMachineSystem::checkStates(State* t_state, Entity* e)
{
	AnimatedSpriteComponent* animated = dynamic_cast<AnimatedSpriteComponent*>(e->getComponent(Types::AnimatedSprite));
	if (animated != nullptr)
	{
		if (m_current == NULL) {
			m_current = new State();
		}

		switch (t_state->getType())
		{
		case States::Interact:
				
			if (animated->getPrevious()->m_type != States::Interact) {
				animated->updateSpriteState(*m_spriteSheets[2]);
				animated->getCurrent()->interact(animated);
				animated->setCurrent(new InteractState());
			}
			break;

		case States::Attack:

			if (animated->getPrevious()->m_type != States::Attack) {
				//animated->updateSpriteState(*m_spriteSheets[2]);
				animated->getCurrent()->attack(animated);
				animated->setCurrent(new AttackState());
			}
			break;

		case States::Idle:
			
			if (animated->getPrevious()->m_type != States::Idle) {
				animated->updateSpriteState(*m_spriteSheets[1]);
				animated->getCurrent()->idle(animated);
				animated->setCurrent(new IdleState());
			}
			break;

			case States::Stunned:
			if (animated->getPrevious()->m_type != States::Stunned) {
				//animated->updateSpriteState(*m_spriteSheets[1]);
				animated->getCurrent()->stunned(animated);
				animated->setCurrent(new StunnedState());
			}
			break;

		case States::Walking:
			if (animated->getPrevious()->m_type != States::Walking) {
				animated->updateSpriteState(*m_spriteSheets[0]);
				animated->getCurrent()->walking(animated);
				animated->setCurrent(new WalkingState());
			}
			break;

		default:
			break;
		}
	}
}


void StateMachineSystem::setRenderer(SDL_Renderer* t_rend)
{
	m_renderer = t_rend;
}

void StateMachineSystem::setupSprites()
{
	SpriteSheet* temp1 = new SpriteSheet;
	temp1->frameSize.x = 90;
	temp1->frameSize.y = 30;
	temp1->name = "RatWalk";
	temp1->t_noOfFrames = 5;
	temp1->frameRate = 3500;

	m_surface = IMG_Load("./Assets/SpriteSheetWalkMouse.png");
	temp1->m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
	SDL_FreeSurface(m_surface);
	m_spriteSheets.push_back(temp1);

	temp1 = NULL;

	SpriteSheet* temp2 = new SpriteSheet;
	temp2->frameSize.x = 90;
	temp2->frameSize.y = 30;
	temp2->name = "RatIdle";
	temp2->t_noOfFrames = 5;
	temp2->frameRate = 8000;

	m_surface = IMG_Load("./Assets/SpriteSheetIdleMouse.png");
	temp2->m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
	SDL_FreeSurface(m_surface);
	m_spriteSheets.push_back(temp2);

	temp2 = NULL;

	SpriteSheet* temp3 = new SpriteSheet;
	temp3->frameSize.x = 90;
	temp3->frameSize.y = 30;
	temp3->name = "RatInteract";
	temp3->t_noOfFrames = 5;
	temp3->frameRate = 8000;

	m_surface = IMG_Load("./Assets/SpriteSheetInteract.png");
	temp3->m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
	SDL_FreeSurface(m_surface);
	m_spriteSheets.push_back(temp3);

	temp3 = NULL;
}

