#include "..//INCLUDE/ButtonSystem.h"

ButtonSystem::ButtonSystem() {

}

ButtonSystem::~ButtonSystem() {

}

void ButtonSystem::updateComponent(Component* c) {
	for (Entity& e : entities) {

	}
}

void ButtonSystem::setStates() {
	for (Entity& e1 : entities) {

		for (Component* c1 : e1.getComponents()) {
			ButtonComponent* btnComp = dynamic_cast<ButtonComponent*>(c1);
			if (btnComp != nullptr) {
				bool acitve = btnComp->getState();
				int btnId = btnComp->getId();

				for (Entity& e2 : entities) {
					for (Component* c2 : e2.getComponents()) {
						TrapComponent* trapComp = dynamic_cast<TrapComponent*>(c2);

						// find the trap with same id to button
						if (trapComp != nullptr && trapComp->getId() == btnId) {
							trapComp->setState(acitve);
						}
					}
				}
			}
		}
	}
}