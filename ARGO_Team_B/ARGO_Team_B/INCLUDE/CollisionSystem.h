#ifndef COLLISION_SYSTEM
#define COLLISION_SYSTEM

#include "System.h"
#include "CollisionComponent.h"
#include "PlayerComponent.h"
#include "ButtonComponent.h"
#include "TrapComponent.h"
#include "HealthComponent.h"
#include "DoorComponent.h"

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
	void searchEntities();

	bool checkCollision(c2Circle t_collider, c2AABB t_otherCollider);
	bool checkCollision(c2AABB t_collider, c2AABB t_otherCollider);
	bool checkCollision(c2AABB t_collider, c2Poly t_otherCollider);

	vector<Entity> m_playerEntitys;
	vector<Entity> m_buttonEntitys;
	vector<Entity> m_trapEntitys;
	vector<Entity> m_doorEntitys;
};
#endif // !COLLISION_SYSTEM