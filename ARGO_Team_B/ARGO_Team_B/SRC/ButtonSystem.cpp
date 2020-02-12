#include "ButtonSystem.h"

ButtonSystem::ButtonSystem() {

}

ButtonSystem::~ButtonSystem() {

}

void ButtonSystem::updateComponent(Component* c) {
	for (Entity& e : entities) {

	}
	setObjectStates();
}

void ButtonSystem::setObjectStates() {
	for (Entity& e1 : entities) {
		if (e1.getType() == Types::Button) {
			ButtonComponent* btnComp = static_cast<ButtonComponent*>(e1.getComponent(Types::Button));
			// check is the button connect with traps
			if (btnComp->getType() == 1) {
				bool acitve = btnComp->getState();
				int btnId = btnComp->getId();

				for (Entity& e2 : entities) {
					if (e2.getType() == Types::Traps) {
						TrapComponent* trapComp = static_cast<TrapComponent*>(e2.getComponent(Types::Traps));

						// find the trap with same id to button
						if (trapComp->getId() == btnId) {
							trapComp->setState(acitve);
						}
					}
				}
			}
			// check is the button connect with door
			else if (btnComp->getType() == 2) {
				int btnId = btnComp->getId();

				for (Entity& e2 : entities) {
					if (e2.getType() == Types::Door) {

						DoorComponent* doorComp = static_cast<DoorComponent*>(e2.getComponent(Types::Door));

						RenderComponent* renderComp = static_cast<RenderComponent*>(e2.getComponent(Types::Render));
						
						// find the trap with same id to button
						if (doorComp->getId() == btnId) {
							doorComp->setState(btnComp->getRedDoor(), btnComp->getGreenDoor());
							if (!btnComp->getRedDoor() || !btnComp->getGreenDoor()) {

								if (btnComp->getRedDoor()) {
									renderComp->setImage("Assets\\greenDoor.png");
								}
								else if (btnComp->getGreenDoor()) {
									renderComp->setImage("Assets\\redDoor.png");
								}
							}
						}

					}
				}
			}

		}
	}
}