#pragma once
#include <vector>
#include <string>

#include "Component.h"
#include "ComponentsEnum.h"

class Entity
{
public:
	Entity() : m_id{ 0 } { };
	~Entity() {};
	void addComponent(Component* t_component, Components t_type) {
		m_components.first.push_back(t_component);
		m_components.second.push_back(t_type);
	};

	int getId() {
		return m_id;
	};

	std::vector<Component*> getComponents() {
		return m_components.first;
	};

	Component* getComponent(Components t_type) {
		for (int i = 0; i < m_components.first.size(); i++) {
			if (m_components.second[i] == t_type) {
				return m_components.first.at(i);
			}
		}
	};

private:
	int m_id;
	std::pair<std::vector<Component*>, std::vector<Components>> m_components;
};
