#ifndef JOININGGAEM
#define JOININGGAME

#pragma once
#include "Online/Client.h"
#include "Observer.h"
#include "Globals.h"

#include "GameScene.h"

#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class JoiningGame {
public:
	JoiningGame();
	~JoiningGame();

	void update(float dt);
	void draw(FontObserver* text, SDL_Renderer* t_renderer);
private:

	not_digit notADigit;
	vector<int> intConverter(string message);
	string preStartCounter;
	
	Client* MyClient;

	int m_startCountdown;
	int m_playerId;
	bool m_gameConnented;

	GameScene* m_gameScene;
};

#endif // !JOININGGAEM