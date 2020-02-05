#pragma once
#include "Component.h"

class TrapComponent :public Component {
public:
	TrapComponent(bool init);
	~TrapComponent();

	void setState(bool state);

private:
	bool m_alive;
};