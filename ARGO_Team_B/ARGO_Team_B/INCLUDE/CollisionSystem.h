#ifndef COLLISION_SYSTEM
#define COLLISION_SYSTEM

#include "System.h"
#include "CollisionComponent.h"
#include "PlayerComponent.h"
#include "ButtonComponent.h"
#include "TrapComponent.h"
#include "HealthComponent.h"
#include "DoorComponent.h"
#include "GoalComponent.h"

#include <vector>
#include "Level.h"
#include "PositionComponent.h"
using namespace std;

class CollisionSystem : public System
{
public:
	CollisionSystem();
	~CollisionSystem();
	void updateComponent(Component* component) override;
	void updateComponent(Level &t_level);
	void tileCollision(float x, float y, float width, float height, Level& t_mazeWalls);
private:

	void searchEntities();

	bool checkCollision(c2Circle t_collider, c2AABB t_otherCollider);
	bool checkCollision(c2AABB t_collider, c2AABB t_otherCollider);
	bool checkCollision(c2AABB t_collider, c2Poly t_otherCollider);

	void searchCheese();

	vector<Entity> m_playerEntitys;
	vector<Entity> m_buttonEntitys;
	vector<Entity> m_trapEntitys;
	vector<Entity> m_doorEntitys;
	vector<Entity> m_goalEntitys;
	float x1, y1;
	PositionComponent* m_positionComp;

};
#endif // !COLLISION_SYSTEM