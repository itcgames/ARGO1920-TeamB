#ifndef PLAYERCOMPONENT
#define PLAYERCOMPONENT


#pragma once
#include "Component.h"

class PlayerComponent : public Component {
public:
	PlayerComponent(int id);
	~PlayerComponent();

	void setMoveable(bool state);
	void setDizzyState(bool dizzy);

	int getId() { return m_id; }
	bool getAlive() { return m_alive; }
	bool getDizzy() { return m_dizzy; }
	bool getMoveable() { return m_moveable; }
private:
	int m_id;
	bool m_alive;
	bool m_moveable;
	bool m_dizzy;
};
#endif