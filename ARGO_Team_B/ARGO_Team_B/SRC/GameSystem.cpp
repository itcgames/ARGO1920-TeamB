#include "Gamesystem.h"

GameSystem::GameSystem() 
{

}

GameSystem::~GameSystem() {

}

void GameSystem::update(float dt) {
	float startCountdown = m_game->getstartCountdown();
	if (startCountdown <= 0) {

		m_game->setRedTeamCheese(m_players[0]->getCheese() + m_players[2]->getCheese());
		m_game->setGreenTeamCheese(m_players[1]->getCheese() + m_players[3]->getCheese());

		float gameTimer = m_game->getGameTimer();
		gameTimer -= dt;
		if (gameTimer <= 0.0f) {
			m_game->setGameover(true);

			int redWinCounter = m_game->getRedWinCounter();
			int greenWinCounter = m_game->getGreenWinCounter();

			// when the timer is 0, the team with more cheese win
			if (m_game->getRedTeamCheese() > m_game->getGreenTeamCheese()) {
				redWinCounter++;
			}
			else if (m_game->getRedTeamCheese() < m_game->getGreenTeamCheese()) {
				greenWinCounter++;
			}
			else {
				redWinCounter++;
				greenWinCounter++;
			}

			// if the game draw at 2:2, get a extra game
			if (redWinCounter >= 3 && greenWinCounter >= 3) {
				redWinCounter = 2;
				greenWinCounter = 2;
			}
			else if (redWinCounter >= 3) {
				// red team win the game
			}
			else if (greenWinCounter >= 3) {
				// green team win the game
			}
			else {
				m_game->setRedWinCounter(redWinCounter);
				m_game->setGreenWinCounter(greenWinCounter);
			}
		}
		else {
			gameTimerString(gameTimer);
			m_game->setGameTimer(gameTimer);
		}
	}
	else {
		startCountdown -= dt;
		m_game->setStartCountdown(startCountdown);
	}
}

void GameSystem::setupComponent()
{
	for (Entity& e : entities) {
		if (e.getType() == Types::Player) {
			PlayerComponent* playerComp = static_cast<PlayerComponent*>(e.getComponent(Types::Player));
			m_players.push_back(playerComp);
		}
		else if (e.getType() == Types::Game) {
			m_gameEntity.push_back(e);
			m_game = static_cast<GameComponent*>(e.getComponent(Types::Game));
		}
	}
}

void GameSystem::gameTimerString(float gameTimer)
{
	int min = gameTimer / 60;
	int sec = gameTimer - min * 60;
	timer = to_string(min) + " : " + to_string(sec);
}

void GameSystem::draw(FontObserver* text) {
	SDL_Color color = { 0, 0, 0 , 255};

	const char* c = timer.data();
	
	text->drawText(1000, 400, 100, 100, c, color, FontObserver::TIMER);
	
	
}