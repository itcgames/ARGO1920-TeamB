#ifndef GAMECOMPONENT
#define GAMECOMPONENT

#pragma once
#include "Component.h"

class GameComponent : public Component {
public :
	GameComponent();
	~GameComponent();

	void setRedTeamCheese(int redCheese);
	int getRedTeamCheese() { return m_redTeamCheese; }

	void setGreenTeamCheese(int greenCheese);
	int getGreenTeamCheese() { return m_greenTeamCheese; }

	void setRedWinCounter(int winCounter);
	int getRedWinCounter() { return m_redWinCounter; }

	void setGreenWinCounter(int winCounter);
	int getGreenWinCounter() { return m_greenWinCounter; }

	void setGameTimer(float gameTimer);
	float getGameTimer() { return m_gameTimer; }

	void setStartCountdown(float startCountdown);
	float getstartCountdown() { return m_startCountdown; }

	void setGameover(bool gameover);
	bool getGameover() { return m_gameover; }

	void resetRound();
	void resetGame();
private:
	int m_redTeamCheese;
	int m_greenTeamCheese;

	int m_redWinCounter;
	int m_greenWinCounter;

	float m_gameTimer;
	float m_startCountdown;
	bool m_gameover;
};

#endif // GAMECOMPONENT