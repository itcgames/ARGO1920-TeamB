#ifndef GAMESYSTEM
#define GAMESYSTEM

#pragma once
#include "System.h"
#include "Entity.h"
#include "Observer.h"

#include "PlayerComponent.h"
#include "GameComponent.h"

class GameSystem : public System{
public:
	GameSystem();
	~GameSystem();

	void update(float dt);
	void setupComponent();

	void draw(FontObserver* text);
private:
	void gameTimerString(float gameTimer);
	vector<PlayerComponent*> m_players;
	vector<Entity> m_gameEntity;
	GameComponent* m_game;

	string timer;
};

#endif // ! GAMEMANAGER
