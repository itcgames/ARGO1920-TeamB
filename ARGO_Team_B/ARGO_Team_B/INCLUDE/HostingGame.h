#ifndef HOSTINGGAME 
#define HOSTINGGAME 

#pragma once
#include "Online/Server.h"
#include "Online/PacketType.h"
#include "Globals.h"
#include "Observer.h"

#include "GameScene.h"

#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <mutex>
#include <thread>

using namespace std;

class HostingGame {
public :
	HostingGame();
	~HostingGame();

	void update(float dt);
	void waitingConnection();
	void draw(FontObserver* text, SDL_Renderer* t_renderer);

	thread m_waitingPlayer;
private:

	not_digit notADigit;
	vector<int> intConverter(string message);
	string preMessage;

	Server* MyServer; //Create server on port 1000

	string m_timerMessage;

	float m_startCountdown;
	int m_playerRequire;

	GameScene* m_gameScene;
};

#endif // !HOSTINGGAME 