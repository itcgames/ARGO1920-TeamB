#pragma once
#include "Component.h"

class PlayerComponent : public Component {
public:
	PlayerComponent(int id);
	~PlayerComponent();

	int getId() { return m_id; }

private:
	int m_id;
	bool m_alive;
};
