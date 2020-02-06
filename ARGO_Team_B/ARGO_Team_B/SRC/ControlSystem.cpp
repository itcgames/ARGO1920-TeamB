#include "ControlSystem.h"

ControlSystem::ControlSystem() {
	m_controller = new Xbox360Controller(0);
}

ControlSystem::~ControlSystem() {}
void ControlSystem::updateComponent(Component* c)
{
	for (Entity& e : entities)
	{
		PositionComponent* posComp = dynamic_cast<PositionComponent*>(c);
		if (posComp != nullptr)
		{

		}
	}
}

void ControlSystem::handleInput()
{
	for (Entity& e : entities)
	{
		for (Component* c : e.getComponents())
		{
			PositionComponent* posComp = dynamic_cast<PositionComponent*>(c);
			if (posComp != nullptr)
			{


				m_controller->checkButton();

				if (m_controller->m_currentState.DpadUp) {
					posComp->moveUp();
				}

				if (m_controller->m_currentState.DpadDown) {
					posComp->moveDown();

					m_controller->checkButton();

					if (m_controller->m_currentState.DpadUp) {
						posComp->moveUp();
					}

					if (m_controller->m_currentState.DpadDown) {
						posComp->moveDown();

						if (m_controller->m_currentState.DpadLeft) {
							posComp->moveLeft();
						}

						if (m_controller->m_currentState.DpadRight) {
							posComp->moveRight();
						}
					}
				}
			}
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

					m_controller->checkButton();

					if (m_controller->m_currentState.DpadUp) {
						posComp->moveUp();
					}

					if (m_controller->m_currentState.DpadDown) {
						posComp->moveDown();
					}

					if (m_controller->m_currentState.DpadLeft) {
						posComp->moveLeft();
					}

					if (m_controller->m_currentState.DpadRight) {
						posComp->moveRight();
					}
				}

			}
		}
	}
