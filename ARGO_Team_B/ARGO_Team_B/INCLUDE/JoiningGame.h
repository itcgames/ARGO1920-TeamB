#ifndef JOININGGAEM
#define JOININGGAME

#pragma once
#include "Client/Client.h"
#include "Observer.h"

#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

struct not_digit {
	bool operator()(const char c)
	{
		return c != ' ' && !isdigit(c);
	}
};

class JoiningGame {
public:
	JoiningGame();
	~JoiningGame();

	void update(float dt);
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