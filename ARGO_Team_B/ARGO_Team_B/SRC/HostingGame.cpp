#include "HostingGame.h"

HostingGame::HostingGame() {
	MyServer = new Server(1111, "149.153.106.159");
	m_startCountdown = 5.0f;
}

HostingGame::~HostingGame() {

}

void HostingGame::update(float dt) {

	if (m_startCountdown <= 0.0f) {
		if (MyServer->getTotalConnections() >= 4) {
			m_startCountdown -= dt;
			int timer = m_startCountdown;
			m_timerMessage = "type: 0, timer: " + to_string(timer);
			//MyServer
			MyServer->SendStringToAll(m_timerMessage);

		}
		else {
			MyServer->ListenForNewConnection();
			m_startCountdown = 5.0f;
		}

	}
	else {
		// game loop here

	}
}

vector<int> HostingGame::intConverter(string message) {
	string::iterator end = std::remove_if(message.begin(), message.end(), notADigit);

	string all_numbers(message.begin(), end);
	std::cout << all_numbers;

	stringstream ss(all_numbers);
	vector<int> vec;
	std::cout << std::endl;
	std::cout << "Let's start next line" << std::endl;
	int i;
	for (; ss >> i;)
	{
		vec.push_back(i);
		cout << i << endl;
	}

	return vec;
}