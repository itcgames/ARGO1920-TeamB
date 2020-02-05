#include "..//INCLUDE/TrapSystem.h"

TrapSystem::TrapSystem() {

}

TrapSystem::~TrapSystem() {

}

void TrapSystem::updateComponent(Component* c) {
	for (Entity& e : entities) {

	}
}

void TrapSystem::setStates() {
	for (Entity& e : entities) {


		for (Component* c1 : e.getComponents()) {
			ButtonComponent* btnComp = dynamic_cast<ButtonComponent*>(c1);
			if (btnComp != nullptr) {
				bool acitve = btnComp->getState();

				for (Component* c2 : e.getComponents()) {
					TrapComponent* trapComp = dynamic_cast<TrapComponent*>(c2);

					if (trapComp != nullptr) {
						trapComp->setState(acitve);
					}
				}
			}
		}
	}
}