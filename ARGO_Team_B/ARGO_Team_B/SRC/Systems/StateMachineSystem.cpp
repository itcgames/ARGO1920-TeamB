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
		case States::WalkingBomb:
			if (animated->getPrevious()->m_type != States::WalkingBomb) {
				animated->updateSpriteState(*m_spriteSheets[3]);
				animated->getCurrent()->walkWithBomb(animated);
				animated->setCurrent(new WalkWithBombState());
			}
			break;
		case States::EatCheese:
			if (animated->getPrevious()->m_type != States::EatCheese) {
				animated->updateSpriteState(*m_spriteSheets[4]);
				animated->getCurrent()->eatCheese(animated);
				animated->setCurrent(new EatCheeseState());
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
	temp1->frameSize.x = 60;
	temp1->frameSize.y = 30;
	temp1->name = "RatWalk";
	temp1->t_noOfFrames = 3;
	temp1->frameRate = 1500;

	m_surface = IMG_Load("./Assets/SpriteSheetWalkMouse.png");
	temp1->m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
	SDL_FreeSurface(m_surface);
	m_spriteSheets.push_back(temp1);

	temp1 = NULL;

	SpriteSheet* temp2 = new SpriteSheet;
	temp2->frameSize.x = 60;
	temp2->frameSize.y = 30;
	temp2->name = "RatIdle";
	temp2->t_noOfFrames = 3;
	temp2->frameRate = 1500;

	m_surface = IMG_Load("./Assets/SpriteSheetIdleMouse.png");
	temp2->m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
	SDL_FreeSurface(m_surface);
	m_spriteSheets.push_back(temp2);

	temp2 = NULL;

	SpriteSheet* temp3 = new SpriteSheet;
	temp3->frameSize.x = 60;
	temp3->frameSize.y = 30;
	temp3->name = "RatInteract";
	temp3->t_noOfFrames = 5;
	temp3->frameRate = 2500;

	m_surface = IMG_Load("./Assets/SpriteSheetInteract.png");
	temp3->m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
	SDL_FreeSurface(m_surface);
	m_spriteSheets.push_back(temp3);

	temp3 = NULL;

	SpriteSheet* temp4 = new SpriteSheet;
	temp4->frameSize.x = 60;
	temp4->frameSize.y = 30;
	temp4->name = "RatWithBomb";
	temp4->t_noOfFrames = 5;
	temp4->frameRate = 2500;

	m_surface = IMG_Load("./Assets/SpriteSheetWalkBombMouse.png");
	temp4->m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
	SDL_FreeSurface(m_surface);
	m_spriteSheets.push_back(temp4);

	temp4 = NULL;

	SpriteSheet* temp5 = new SpriteSheet;
	temp5->frameSize.x = 60;
	temp5->frameSize.y = 30;
	temp5->name = "RatEatCheese";
	temp5->t_noOfFrames = 3;
	temp5->frameRate = 1500;

	m_surface = IMG_Load("./Assets/SpriteSheetMouseCheese.png");
	temp5->m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
	SDL_FreeSurface(m_surface);
	m_spriteSheets.push_back(temp5);

	temp5 = NULL;
}

