#ifndef COLLISION_SYSTEM
#define COLLISION_SYSTEM

#include "System.h"
#include "CollisionComponent.h"
#include "PlayerComponent.h"
#include "ButtonComponent.h"
#include "TrapComponent.h"
#include "HealthComponent.h"
#include "GoalComponent.h"
#include <vector>
using namespace std;

class CollisionSystem : public System
{
public:
	CollisionSystem();
	~CollisionSystem();
	void updateComponent(Component* component) override;
	void updateComponent();

private:
	void searchPlayer();
	void searchButton();
	void searchTrap();
	void searchCheese();
	bool checkCollision(c2Circle t_collider, c2Circle t_otherCollider);

	vector<Entity> m_playerEntitys;
	vector<Entity> m_buttonEntitys;
	vector<Entity> m_trapEntitys;
	vector<Entity> m_goalEntitys;
};
#endif // !COLLISION_SYSTEM