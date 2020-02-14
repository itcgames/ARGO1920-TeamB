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

	void setInteract(bool interact);
	bool getInteract() { return m_interact; }

	void setSwipeCooldown(float time);
	float getSwipeCooldown() { return m_swipeCooldown; }
private:
	int m_id;
	bool m_alive;
	bool m_moveable;
	bool m_dizzy;

	bool m_interact;
	float m_swipeCooldown;
};
#endif