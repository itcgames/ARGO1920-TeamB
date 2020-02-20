#ifndef ENTITY_H
#define ENTITY_H


#include <vector>
#include <string>

#include "Component.h"
#include "Enums.h"

class Entity
{
public:
	static int m_instanceCount;

	Entity(EntityType t_type = EntityType::Default) :
		m_entityType(t_type)
	{
		m_id = m_instanceCount++;
	};
	~Entity() {};
	void addComponent(Component* t_component, Types t_type) {
		m_components.first.push_back(t_component);
		m_components.second.push_back(t_type);
	};

	void removeComponent(Types t_type)
	{
		for (int i = 0; i < m_components.first.size(); i++)
		{
			if (m_components.second[i] == t_type)
			{

			}
		}
	}

	int getId() {
		return m_id;
	};

	std::vector<Component*> getComponents() {
		return m_components.first;
	};

	Component* getComponent(Types t_type) {
		for (int i = 0; i < m_components.first.size(); i++) {
			if (m_components.second[i] == t_type) {
				return m_components.first.at(i);
			}
		}
	};

	Types getType() { return m_components.second.at(0); } // all Player Types have to be first component passed 

	EntityType getEntityType() { return m_entityType; }
private:
	int m_id;
	EntityType m_entityType;
	std::pair<std::vector<Component*>, std::vector<Types>> m_components;
};

#endif
