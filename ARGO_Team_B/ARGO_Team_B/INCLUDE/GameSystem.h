#ifndef GAMESYSTEM
#define GAMESYSTEM

#pragma once
#include "System.h"
#include "Entity.h"
#include "Observer.h"

#include "PlayerComponent.h"
#include "GameComponent.h"
#include "PositionComponent.h"
#include "RenderComponent.h"

/// <summary>
/// get the data of the monment player collect a cheese
/// </summary>
class tempCheeseData {
public:
	tempCheeseData(int count, int x, int y, int id) {
		m_time = m_initTime;
		m_count = count;
		posX = x;
		posY = y;
		originY = y;
		playerId = id;
	}

	void setTime(float time) {
		m_time = time;
		posY = originY - 30 * (2 - time / m_initTime);
	}
	float getTime() { return m_time; }

	int m_count;
	int posX;
	int posY;
	int playerId;
private:
	float m_initTime = 3.0f;
	float m_time;
	int originY;
};

class GameSystem : public System{
public:
	GameSystem();
	~GameSystem();

	void update(float dt);
	void setupComponent();

	void draw(FontObserver* text);
private:
	void gameTimerString(float gameTimer);
	vector<Entity> m_playerEntities;
	vector<PlayerComponent*> m_players;
	vector<Entity> m_gameEntity;

	vector<tempCheeseData*> m_cheeseTextData;

	GameComponent* m_game;
	RenderComponent* m_cheese;

	string timer;
};

#endif // ! GAMEMANAGER
