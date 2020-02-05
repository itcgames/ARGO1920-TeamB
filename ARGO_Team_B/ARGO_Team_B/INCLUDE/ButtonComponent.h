#pragma once
#include "Component.h"

class ButtonComponent : public Component {
public:
	ButtonComponent(bool init);
	~ButtonComponent();

	void setState(bool state);
	bool getState();
private:
	bool m_acitve;

};