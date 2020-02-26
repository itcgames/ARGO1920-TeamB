#include "JoiningGame.h"

JoiningGame::JoiningGame() {
	m_startCountdown = 5;
	m_playerId = 0;
	m_gameConnented = false;
	//
	//MyClient = new Client("149.153.106.159", 1111); //Create client to connect to server on port 1111
}

JoiningGame::~JoiningGame() {

}

void JoiningGame::update(float dt) {

	if (MyClient == nullptr) {
		/*
		get input from player
		*/

		MyClient = new Client("149.153.106.159", 1111);
	}

	if (!m_gameConnented) {
		if (!MyClient->Connect()) {
			delete MyClient;
		}
		else {
			m_playerId = 0;
			m_gameConnented = true;
		}
	}
	else {
		currentTime = SDL_GetTicks();

		if (currentTime < startTime) {

			// get start time from the server 
			if (preStartCounter != MyClient->getStartCountdown()) {
				preStartCounter = MyClient->getStartCountdown();
				 temp = intConverter(preStartCounter);
				if (temp.size() == 1) {
					startTime = temp[0];
				}

			}

			//cout << "Timer: " << m_startCountdown << endl;
		}
		else {
			//get data from server
			if (prePlayerData != MyClient->getPlayerData()) {
				prePlayerData = MyClient->getPlayerData();
				temp = intConverter(prePlayerData);
				for (int i = 0; i < temp.size(); i++) {
					cout << temp[i] << endl;
				}
				m_gameScene->setDataToPlayer(temp);
			}

			// game play here
			m_gameScene->update(dt);

			//transfer current player data
			string m_playerState = m_gameScene->playerInfo(1);
			MyClient->SendString(m_playerState, PacketType::PlayerData);

		}
	}
}

void JoiningGame::draw(FontObserver* text, SDL_Renderer* t_renderer)
{
	if (m_startCountdown > 0.0f) {
		string cheeseCounter = "Waiting for Server ";
		const char* c = cheeseCounter.data();
		SDL_Color color = { 1, 1, 1 , 255 };
		text->drawText(860, 510, 200, 100, c, color, FontObserver::TIMER1);
	}
	else {
		if (m_gameScene == NULL) {
			m_gameScene = new GameScene(t_renderer);
		}
		else {
			m_gameScene->render();
		}
	}
}

vector<int> JoiningGame::intConverter(string message) {
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