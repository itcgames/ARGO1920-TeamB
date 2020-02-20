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
#include "PositionComponent.h"
#include "BombComponent.h"

#include <vector>
#include "Observer.h"
#include "Level.h"
using namespace std;

class CollisionSystem : public System 
{
public:
	CollisionSystem();
	~CollisionSystem();
	void updateComponent(Component* component) override;
	void updateComponent(Level &t_level,AudioObserver * t_observer);
	void tileCollision(float x, float y, float width, float height, Level& t_mazeWalls,AudioObserver* t_observer);
private:

	void searchEntities();

	bool checkCollision(c2Circle t_collider, c2AABB t_otherCollider);
	bool checkCollision(c2AABB t_collider, c2AABB t_otherCollider);
	bool checkCollision(c2AABB t_collider, c2Poly t_otherCollider);

	void searchCheese();

	void bombCollision(AudioObserver* t_observer, Level* t_level);
	void TileBombCollision(Level* t_level, BombComponent* t_bomb);

	vector<Entity> m_playerEntitys;
	vector<Entity> m_buttonEntitys;
	vector<Entity> m_trapEntitys;
	vector<Entity> m_doorEntitys;
	vector<Entity> m_goalEntitys;
	vector<Entity> m_bombEntitys;
	float x1, y1;
	PositionComponent* m_positionComp;
};
#endif // !COLLISION_SYSTEM