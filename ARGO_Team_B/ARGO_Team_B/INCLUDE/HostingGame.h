#ifndef HOSTINGGAME 
#define HOSTINGGAME 

#pragma once
#include "Online/Server.h"
#include "Online/PacketType.h"
#include "Observer.h"
#include "Enums.h"

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

	float m_startCountdown;
	int m_playerRequire;
	int m_idForPlayer;

	GameScene* m_gameScene;
	SDL_Renderer* m_renderer;

	string prePlayerData;
	vector<int> temp;

	Uint32 startTime;
	Uint32 currentTime;
};

#endif // !HOSTINGGAME 