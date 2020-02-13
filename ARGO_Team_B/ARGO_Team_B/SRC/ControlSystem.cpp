#include "ControlSystem.h"

ControlSystem::ControlSystem() {
		Xbox360Controller * controller= new Xbox360Controller(0);
		m_controllers.push_back(controller);
	
}

ControlSystem::~ControlSystem() {}
void ControlSystem::updateComponent(Component* c)
{
	for (Entity& e : entities)
	{
		ControlComponent* cont = dynamic_cast<ControlComponent*>(e.getComponent(Types::Controller));

		if (cont != NULL)
		{
			cont->handleInput();
		}
	}
}

void ControlSystem::handleInput(float dt) {
	for (Entity& e : entities)
	{
		ControlComponent* cont = dynamic_cast<ControlComponent*>(e.getComponent(Types::Controller));

		if (cont != NULL)
		{
			cont->handleInput();
		}

		PlayerComponent* playerComp = dynamic_cast<PlayerComponent*>(e.getComponent(Types::Player));

		if (playerComp->getSwipeCooldown() > 0.0f) {
			float timer = playerComp->getSwipeCooldown();
			timer -= dt;
			playerComp->setSwipeCooldown(timer);
		}
	}
}

void ControlSystem::handleInput(SDL_Keycode key)
{
	for (Entity& e : entities)
	{
		for (Component* c : e.getComponents())
		{
			PositionComponent* posComp = dynamic_cast<PositionComponent*>(c);
			if (posComp != nullptr)
			{
				switch (key)
				{
					case SDLK_a:
						posComp->moveLeft();
						break;
					case SDLK_d:
						posComp->moveRight();
						break;
					case SDLK_w:
						posComp->moveUp();
						break;
					case SDLK_s:
						posComp->moveDown();
						break;
					default:
						break;
				}

				//for (int i = 0; i < NOOFPLAYERS; i++)
				//	{
				//		if (e.getId() == m_controllers.at(i)->getID())
				//		{
				//			PositionComponent* posComp = dynamic_cast<PositionComponent*>(c);
				//			if (posComp != nullptr)
				//			{

				//			m_controllers.at(i)->checkButton();

				//			if (m_controllers.at(i)->m_currentState.DpadUp) {
				//				posComp->moveUp();
				//			}

				//			if (m_controllers.at(i)->m_currentState.DpadLeft) {
				//				posComp->moveLeft();
				//			}

				//			if (m_controllers.at(i)->m_currentState.DpadRight) {
				//				posComp->moveRight();
				//			}

				//			if (m_controllers.at(i)->m_currentState.DpadDown) {
				//				posComp->moveDown();
				//			}// !if
				//			}
				//		} // !if
				//	} // !if
				//}// !if

			}// !for
		}// !if
	}// !for
} // !void
