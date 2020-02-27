#ifndef TRAPCOMPONENT
#define TRAPCOMPONENT

#include "Component.h"

class TrapComponent :public Component {
public:
	TrapComponent(bool init, int id);
	~TrapComponent();

	void setState(bool state);
	int getId() { return m_id; }
	bool getAlive() { return m_alive; }

private:
	bool m_alive;
	int m_id;
};
#endif