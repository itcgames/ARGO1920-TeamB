#include "GameComponent.h"

GameComponent::GameComponent()
{
	resetGame();
}

GameComponent::~GameComponent() {

}

void GameComponent::setRedTeamCheese(int redCheese)
{
	m_redTeamCheese = redCheese;
}

void GameComponent::setGreenTeamCheese(int greenCheese)
{
	m_greenTeamCheese = greenCheese;
}

void GameComponent::setRedWinCounter(int winCounter)
{
	m_redWinCounter = winCounter;
}

void GameComponent::setGreenWinCounter(int winCounter)
{
	m_greenWinCounter = winCounter;
}

void GameComponent::setGameTimer(float gameTimer)
{
	m_gameTimer = gameTimer;
}

void GameComponent::setStartCountdown(float startCountdown)
{
	m_startCountdown = startCountdown;
}

void GameComponent::setGameover(bool gameover)
{
	m_gameover = gameover;
}



void GameComponent::resetRound()
{
	m_redTeamCheese = 0;
	m_greenTeamCheese = 0;
	m_gameover = false;

	// Release
	m_gameTimer = 120.0f;
	m_startCountdown = 3.0f;

	//Debug
	// m_gameTimer = 3;
	// m_startCountdown = 0;

}

/// <summary>
/// reset all state
/// </summary>
void GameComponent::resetGame()
{
	m_redWinCounter = 0;
	m_greenWinCounter = 0;
	resetRound();
}