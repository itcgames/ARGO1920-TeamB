#include "Gamesystem.h"

GameSystem::GameSystem() 
{
	winTextColor = { 0,0,0,255 };
}

GameSystem::~GameSystem() {

}

void GameSystem::update(float dt,AudioObserver*t_observer) {
	// Release timer
	float startCountdown = m_game->getstartCountdown();

	// Debug timer
	//float startCountdown = 0;

	if (startCountdown <= 0) {

		m_game->setRedTeamCheese(m_players[0]->getCheeseCounter() + m_players[2]->getCheeseCounter());
		m_game->setGreenTeamCheese(m_players[1]->getCheeseCounter() + m_players[3]->getCheeseCounter());

		for (Entity& player : m_playerEntities) {
			PositionComponent* playerPos = static_cast<PositionComponent*>(player.getComponent(Types::Position));
			PlayerComponent* playerComp = static_cast<PlayerComponent*>(player.getComponent(Types::Player));

			if (playerComp->getACheese()) {
				tempCheeseData* info;
				
				if (playerComp->getId() == 1 || playerComp->getId() == 3) {
					info = new tempCheeseData(m_game->getRedTeamCheese(), playerPos->getPositionX(), playerPos->getPositionY(), playerComp->getId());
				}
				else if (playerComp->getId() == 2 || playerComp->getId() == 4) {
					info = new tempCheeseData(m_game->getGreenTeamCheese(), playerPos->getPositionX(), playerPos->getPositionY(), playerComp->getId());
				}
				
				m_cheeseTextData.push_back(info);
				playerComp->setGetCheeseOff();
			}
		}

		for (int i = 0; i < m_cheeseTextData.size(); i++) {
			float textTimer = m_cheeseTextData[i]->getTime();
			textTimer -= dt;
			m_cheeseTextData[i]->setTime(textTimer);	
			if (textTimer <= 0.0f) {
				//m_cheeseTextData.erase(m_cheeseTextData.begin());
				m_cheeseTextData.erase(m_cheeseTextData.begin() + i);
			}
		}

		float gameTimer = m_game->getGameTimer();
		gameTimer -= dt;
		m_game->setGameTimer(gameTimer);

		// round end
		if (gameTimer <= 0.0f) {
			m_game->setGameover(true);
		

			int redWinCounter = m_game->getRedWinCounter();
			int greenWinCounter = m_game->getGreenWinCounter();

			// when the timer is 0, the team with more cheese win
			if (m_game->getRedTeamCheese() > m_game->getGreenTeamCheese()) {
				redWinCounter++;
				winTextColor = { 255,0,0,255 };
				winInfo = "RED TEAM WIN!";
				t_observer->onNotify(AudioObserver::YOUWIN);
			}
			else if (m_game->getRedTeamCheese() < m_game->getGreenTeamCheese()) {
				greenWinCounter++;
				winTextColor = { 0,255,0,255 };
				winInfo = "GREEN TEAM WIN!";
				t_observer->onNotify(AudioObserver::YOUWIN);
			}
			else {
				winTextColor = { 255,255,0,255 };
				winInfo = "DRAW!";
				redWinCounter++;
				greenWinCounter++;
				t_observer->onNotify(AudioObserver::DRAW);
			}

			// if the game draw at 2:2, get a extra game
			if (redWinCounter >= 3 && greenWinCounter >= 3) {
				redWinCounter = 2;
				greenWinCounter = 2;
			}
			else if (redWinCounter >= 3 && redWinCounter > greenWinCounter) {
				// red team win the game
				winTextColor = { 255,0,0,255 };
				winInfo = "RED TEAM WIN THE GAME!";
				m_game->setGameCount(-1); // goes to main menu scene elsewhere
			}
			else if (greenWinCounter >= 3 && redWinCounter < greenWinCounter) {
				// green team win the game
				winTextColor = { 0,255,0,255 };
				winInfo = "GREEN TEAM WIN THE GAME!";
				m_game->setGameCount(-1); // goes to main menu scene elsewhere
			}
			
			if (greenWinCounter == redWinCounter && m_game->getGameCount() >= 5) {
				// draw game..
				winTextColor = { 0,0,255,255 };
				winInfo = "THE GAME WAS A DRAW..";
				t_observer->onNotify(AudioObserver::DRAW);
			}
			else {
				m_game->setRedWinCounter(redWinCounter);
				m_game->setGreenWinCounter(greenWinCounter);
			}


		}
		else {
			gameTimerString(gameTimer);
		}
	}
	else {
		startCountdown -= dt;
		m_game->setStartCountdown(startCountdown);

		for (PlayerComponent* playerComp : m_players) {
			playerComp->setMoveable(false);
		}

		if (startCountdown <= 0) {
			for (PlayerComponent* playerComp : m_players) {
				playerComp->setMoveable(true);
			}
		}

	}
}

void GameSystem::setupComponent()
{
	for (Entity& e : entities) {
		if (e.getType() == Types::Player) {
			m_playerEntities.push_back(e);
			PlayerComponent* playerComp = static_cast<PlayerComponent*>(e.getComponent(Types::Player));
			m_players.push_back(playerComp);
		}
		else if (e.getType() == Types::Game) {
			m_gameEntity.push_back(e);
			m_game = static_cast<GameComponent*>(e.getComponent(Types::Game));
			m_cheese = static_cast<RenderComponent*>(e.getComponent(Types::Render));
		}
	}
}

void GameSystem::gameTimerString(float gameTimer)
{
	int min = gameTimer / 60;
	int sec = gameTimer - min * 60;
	timer = to_string(min) + " : " + to_string(sec);
}

void GameSystem::draw(FontObserver* text, float restartTimer) {
	SDL_Color color = { 0, 0, 0 , 255 };

	// show the timer 
	if (m_game->getstartCountdown() <= 0.0f) {
		if (m_game->getGameTimer() > 0.0f) {
			const char* c = timer.data();

			if (m_game->getGameTimer() <= 30.0f) {
				color = { 225, 0, 0 , 255 };
			}
			text->drawText(860, 510, 100, 100, c, color, FontObserver::TIMER2);

			for (tempCheeseData* textData : m_cheeseTextData) {
				string cheeseCounter = to_string(textData->m_count);
				const char* c = cheeseCounter.data();

				if (textData->playerId == 1 || textData->playerId == 3) {
					color = { 225, 0, 0 , (Uint8)(255 * (textData->getTime() / 3.0f)) };
				}
				else if (textData->playerId == 2 || textData->playerId == 4) {
					color = { 0, 225, 0 , (Uint8)(255 * (textData->getTime() / 3.0f)) };
				}

				m_cheese->draw(textData->posX - 30, textData->posY, 0, (Uint8)(255 * (textData->getTime() / 3.0f)));
				text->drawText(textData->posX, textData->posY, 30, 30, c, color, FontObserver::COUNTER);
			}
		}
		else {
			// win condition part

			if (restartTimer <= 7.0f) {

				for (PlayerComponent* m_player : m_players) {
					string cheeseForPlayer = "Player " + to_string(m_player->getId()) + " : " + to_string(m_player->getCheeseCounter());
					const char* c = cheeseForPlayer.data();
					if (m_player->getId() == 1 || m_player->getId() == 3) {
						color = { 225, 0, 0 , 255 };
					}
					else if (m_player->getId() == 2 || m_player->getId() == 4) {
						color = { 0, 255, 0 , 255 };
					}

					text->drawText((500 * m_player->getId() - 400), 800, 200, 50, c, color, FontObserver::COUNTER);
				}

				if (restartTimer <= 6.0f) {
					string teamCheese = "Red Team: " + to_string(m_game->getRedTeamCheese());
					color = { 225, 0, 0 , 255 };
					m_cheese->draw(360, 215, 0, 200, 200);
					text->drawText(360, 400, 200, 50, teamCheese.data(), color, FontObserver::COUNTER);

					teamCheese = "Green Team: " + to_string(m_game->getGreenTeamCheese());
					color = { 0, 225, 0 , 255 };
					m_cheese->draw(1320, 215, 0, 200, 200);
					text->drawText(1320, 400, 200, 50, teamCheese.data(), color, FontObserver::COUNTER);
				}

				if (restartTimer <= 5.0f) {
					text->drawText(785, 315, 300, 100, winInfo.data(), winTextColor, FontObserver::COUNTER);

					int restart = restartTimer;
					string restartText = to_string(restart);
				}
			}
			else {
				color = { 1,1,1,255 };
				text->drawText(760, 420, 400, 200, "TIME UP!", color, FontObserver::COUNTER);
			}

		}
	}
	else {
		float countdown = m_game->getstartCountdown() + 1;
		string timerText = to_string((int)countdown);
		const char* startTimer = timerText.data();
		text->drawText(860, 485, 100, 150, startTimer, color, FontObserver::TIMER1);

		// show rat with player number at start
		for (Entity& player : m_playerEntities) {
			PositionComponent* playerPos = static_cast<PositionComponent*>(player.getComponent(Types::Position));
			PlayerComponent* playerComp = static_cast<PlayerComponent*>(player.getComponent(Types::Player));
			
			string playerID = "Player " + to_string(playerComp->getId());
			const char* playerText = playerID.data();
			if (playerComp->getId() == 1 || playerComp->getId() == 3) {
				color = { 200, 0, 0 , 255 };
			}
			else if (playerComp->getId() == 2 || playerComp->getId() == 4) {
				color = { 0, 200, 0 , 255 };
			}

			int width = 90 * ( 2 - countdown / 4.0f);
			int height = 30 * (2 - countdown / 4.0f);

			int x = playerPos->getPositionX();
			int y = playerPos->getPositionY() - height;


			text->drawText(x, y, width, height, playerText, color, FontObserver::PLAYERTAG);
		}


	}
	

}