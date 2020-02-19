#ifndef HOSTINGGAME 
#define HOSTINGGAME 

#pragma once
#include "Server/Server.h"

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


class HostingGame {
public :
	HostingGame();
	~HostingGame();

	void update(float dt);
private:
	not_digit notADigit;
	vector<int> intConverter(string message);
	string preMessage;

	Server* MyServer; //Create server on port 1000

	string m_timerMessage;

	float m_startCountdown;

};

#endif // !HOSTINGGAME 