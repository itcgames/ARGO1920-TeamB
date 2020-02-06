#pragma once
#include "Component.h"

class DoorComponent : public Component {
public:
	DoorComponent(int id);
	~DoorComponent();

	void setState(bool red, bool green);

	bool getRedDoor() { return m_redOpen; }
	bool getGreenDoor() { return m_greenOpen; }

private:
	int m_id;
	bool m_redOpen;
	bool m_greenOpen;
};