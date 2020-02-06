#pragma once
#include "Component.h"

class ButtonComponent : public Component {
public:
	ButtonComponent(bool init, int id);
	~ButtonComponent();

	void setState(bool state);
	bool getState();

	int getId(){return m_id;}
private:
	bool m_acitve;
	int m_id;

};