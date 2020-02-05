#pragma once
#include <vector>
#include "Component.h"

class Entity
{
public:
	static int m_instanceCount;

	Entity() {
		m_id = m_instanceCount++;
	};
	~Entity() {};
	void addComponent(Component* component) {
		m_components.push_back(component);
	};

	int getId() {
		return m_id;
	};
	std::vector<Component*> getComponents() {
		return m_components;
	};
private:
	int m_id;
	std::vector<Component*> m_components;
};

