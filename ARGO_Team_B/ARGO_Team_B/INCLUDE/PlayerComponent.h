#ifndef PLAYERCOMPONENT
#define PLAYERCOMPONENT


#pragma once
#include "Component.h"

class PlayerComponent : public Component {
public:
	PlayerComponent(int id);
	~PlayerComponent();

	void setMoveable(bool state);

	int getId() { return m_id; }
	bool getAlive() { return m_alive; }
	bool getMoveable() { return m_moveable; }
private:
	int m_id;
	bool m_alive;
	bool m_moveable;
};
#endif