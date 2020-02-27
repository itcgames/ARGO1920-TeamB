#ifndef BOMBSYSTEM
#define BOMBSYSTEM

#include "System.h"

#include "BombComponent.h"
#include "PlayerComponent.h"
#include "PositionComponent.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "Observer.h"
#include "ControlComponent.h"
	
class BombSystem : public System {
public:
	BombSystem();
	~BombSystem();

	void updateComponent(Component* c) override;
	void updateComponent(float dt, AudioObserver* t_observer,SDL_Rect & t_view);

	bool m_isScreenShaking{ false };
	int screenShakeAmountX{ 5 };
	int screenShakeAmountY{ 5 };

	void ScreenShake(SDL_Rect & t_view);

private:
	vector<Entity> m_playerEntitys;
	vector<Entity> m_bombEntitys;

	void searchEntities();
};

#endif