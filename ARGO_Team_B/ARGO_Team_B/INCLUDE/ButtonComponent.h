#pragma once
#include "Component.h"

class ButtonComponent : public Component {
public:
	ButtonComponent(bool init, int id);
	~ButtonComponent();

	void setState(bool state);

	bool getState();
	bool getAlive();

	int getId(){return m_id;}
private:
	bool m_acitve;
	bool m_alive;
	int m_id;

};