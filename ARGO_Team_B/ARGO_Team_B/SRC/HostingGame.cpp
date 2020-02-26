#include "HostingGame.h"

HostingGame::HostingGame()
{
	MyServer = new Server(1111, "149.153.106.159");
	m_startCountdown = 5.0f;
	m_playerRequire = 1;
	
	//m_waitingPlayer = thread(this->waitingConnection);
	//m_waitingPlayer.join();
}

HostingGame::~HostingGame() {

}

void HostingGame::waitingConnection() {
	if (MyServer->getTotalConnections() < m_playerRequire) {
		cout << "waiting for players" << endl;
		MyServer->ListenForNewConnection();
		m_startCountdown = 10.0f;
	}
}

void HostingGame::update(float dt) {
	waitingConnection();

	if (m_startCountdown > 0.0f) {
		if (MyServer->getTotalConnections() >= m_playerRequire) {
			m_startCountdown -= dt;
			int timer = m_startCountdown + 1;
			string m_timerMessage = "timer: " + to_string(timer);
			//MyServer
			MyServer->SendStringToAll(m_timerMessage, PacketType::StartCountdown);
			cout << m_timerMessage << endl;
		}
	}
	else {
		// game loop here

		m_gameScene->update(dt);

		// transfer game data to client 
		float gameStartCountdown = m_gameScene->gameStartCountdown();
		float ingameTimer = m_gameScene->ingameTimer();
		string m_gameState;
		if (gameStartCountdown > 0) {
			m_gameState = "start in : " + to_string(gameStartCountdown);
			MyServer->SendStringToAll(m_gameState, PacketType::StartGameTimer);
		}
		else {
			m_gameState = "Timer : " + to_string(ingameTimer);
			MyServer->SendStringToAll(m_gameState, PacketType::InGameTimer);

			//transfer current player data
			string m_playerState = m_gameScene->playerInfo(1);
			MyServer->SendStringToAll(m_playerState, PacketType::PlayerData);
		}



	}

}

void HostingGame::draw(FontObserver* text, SDL_Renderer* t_renderer)
{
	SDL_Color color = { 1, 1, 1 , 255 };

	if (MyServer->getTotalConnections() < m_playerRequire) {
		string startTiemr = "Waitint for new player";
		const char* c = startTiemr.data();

		text->drawText(660, 510, 400, 100, c, color, FontObserver::TIMER1);

	}
	else {
		if (m_startCountdown > 0.0f) {
			int timer = m_startCountdown + 1;
			string startTiemr = "Game start in " + to_string(timer);
			const char* c = startTiemr.data();
			color = { 1, 1, 1 , 255 };
			text->drawText(760, 510, 200, 100, c, color, FontObserver::TIMER1);
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