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
	void searchPlayer();
	void searchButton();
	void searchTrap();
	void searchCheese();
	bool checkCollision(c2Circle t_collider, c2Circle t_otherCollider);

	vector<Entity> m_playerEntitys;
	vector<Entity> m_buttonEntitys;
	vector<Entity> m_trapEntitys;
	vector<Entity> m_goalEntitys;
	float x1, y1, width1, height1;
	PositionComponent* m_positionComp;
};
#endif // !COLLISION_SYSTEM