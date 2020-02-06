#pragma once
#include "Component.h"

class ButtonComponent : public Component {
public:
	ButtonComponent(bool init, int id);

	ButtonComponent(bool red, bool green, int id);


	~ButtonComponent();

	void setState(bool state);

	void setRedDoor(bool state);
	void setGreenDoor(bool state);

	bool getState();
	bool getAlive();

	int getId();
private:
	bool m_acitve;
	bool m_alive;

	bool m_redTeam;
	bool m_greenTeam;

	int m_id;

};