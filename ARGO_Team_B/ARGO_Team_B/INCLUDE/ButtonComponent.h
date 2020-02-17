#ifndef BUTTONCOMPONENT
#define BUTTONCOMPONENT

#pragma once
#include "Component.h"
class ButtonComponent : public Component {
public:
	ButtonComponent(bool init, int id, int type);

	~ButtonComponent();

	void setState(bool state);

	void setRedDoor(bool state);
	void setGreenDoor(bool state);

	bool getState();
	bool getAlive();

	bool getRedDoor();
	bool getGreenDoor();

	int getId();
	int getType();
private:
	bool m_acitve;
	bool m_alive;

	bool m_redTeam;
	bool m_greenTeam;

	int m_id;
	int m_type;
};
#endif