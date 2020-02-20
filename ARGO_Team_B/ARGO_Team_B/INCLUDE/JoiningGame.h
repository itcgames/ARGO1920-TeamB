#ifndef JOININGGAEM
#define JOININGGAME

#pragma once
#include "Online/Client.h"
#include "Observer.h"
#include "Globals.h"

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

	void update();
	void draw(FontObserver* text);
private:

	not_digit notADigit;
	vector<int> intConverter(string message);
	string preStartCounter;
	
	Client* MyClient;

	int m_startCountdown;
	int m_playerId;
	bool m_gameConnented;
};

#endif // !JOININGGAEM