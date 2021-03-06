#include "MenuScene.h"

/// <summary>
/// overloaded constructor of the menu scene
/// set up the background , menu buttons , selector, background,audio observer
/// </summary>
/// <param name="t_renderer"></param>
/// <param name="t_gamestate"></param>
/// <param name="t_control"></param>
MenuScene::MenuScene(SDL_Renderer* t_renderer, GameStates* t_gamestate, ControlComponent* t_control) :
	m_currentState(t_gamestate),
	m_buttomTimer(0.0f),
	m_timerOffset(0.2f)

{
	if (!m_bg.loadFromFile("./Assets/menu/background_final.png", t_renderer, 1))
	{
		printf("Failed to load BG texture!\n");
	}
	m_bgX = 0;
	m_bgY = 0;
	m_bgW = m_bg.getWidth();
	m_bgH = m_bg.getHeight();

	if (!m_botPlay.loadFromFile("./Assets/menu/botPlay.png", t_renderer, 1))
	{
		printf("Failed to load play texture!\n");
	}
	m_playX = 200;
	m_playY = 150;
	m_playW = m_botPlay.getWidth();
	m_playH = m_botPlay.getHeight();

	if (!m_localPlay.loadFromFile("./Assets/menu/localPlay.png", t_renderer, 1))
	{
		printf("Failed to load play texture!\n");
	}
	m_localPlayX = 200;
	m_localPlayY = 250;
	m_localPlayW = m_localPlay.getWidth();
	m_localPlayH = m_localPlay.getHeight();

	if (!m_onlinePlay.loadFromFile("./Assets/menu/onlinePlay.png", t_renderer, 1))
	{
		printf("Failed to load play texture!\n");
	}
	m_onlinePlayX = 200;
	m_onlinePlayY = 350;
	m_onlinePlayW = m_onlinePlay.getWidth();
	m_onlinePlayH = m_onlinePlay.getHeight();

	if (!m_Credits.loadFromFile("./Assets/menu/credits.png", t_renderer, 1))
	{
		printf("Failed to load play texture!\n");
	}
	m_CreditsX = 200;
	m_CreditsY = 450;
	m_CreditsW = m_Credits.getWidth();
	m_CreditsH = m_Credits.getHeight();

	if (!m_quitGame.loadFromFile("./Assets/menu/quitGame.png", t_renderer, 1))
	{
		printf("Failed to load play texture!\n");
	}
	m_quitX = 200;
	m_quitY = 550;
	m_quitW = m_quitGame.getWidth();
	m_quitH = m_quitGame.getHeight();

	if (!m_selector.loadFromFile("./Assets/menu/selector.png", t_renderer, 1))
	{
		printf("Failed to load BG texture!\n");
	}
	m_selectorX = m_playX;
	m_selectorY = m_playY;
	m_selectorW = m_selector.getWidth();
	m_selectorH = m_selector.getHeight();

	m_controller = t_control->getController();

	m_observer = new AudioObserver();
	m_observer->load();
	m_observer->StartBGM(2);
}
/// <summary>
/// menu scene destructor
/// </summary>
MenuScene::~MenuScene()
{
}

/// <summary>
/// navigate the selector throught the menu buttons
/// </summary>
void MenuScene::handleEvents()
{
	m_controller->checkButton();
	int m_movementY = 100;
	if (m_buttomTimer <= 0.0f) {

		if (m_controller->m_currentState.LeftThumbStick.y < -m_controller->dpadThreshold)
		{
			m_selectorY = m_selectorY - m_movementY;
			m_buttomTimer = m_timerOffset;
			m_observer->onNotify(AudioObserver::CLICK);
		}
		else if (m_controller->m_currentState.LeftThumbStick.y > m_controller->dpadThreshold)
		{
			m_selectorY = m_selectorY + m_movementY;
			m_buttomTimer = m_timerOffset;
			m_observer->onNotify(AudioObserver::CLICK);
		}
	}

	if (m_selectorY > 550)
	{
		m_selectorY = 100;
	}
	if (m_selectorY < 150)
	{
		m_selectorY = 550;
	}

}
/// <summary>
/// update the button timer, so it doesnt repeat itself when pressed
/// </summary>
/// <param name="dt"></param>
void MenuScene::update(float dt)
{
	if (m_buttomTimer > 0.0f) {
		m_buttomTimer -= dt;
	}
}
/// <summary>
/// render the  background , selector and menu buttons
/// </summary>
/// <param name="t_renderer"></param>
void MenuScene::render(SDL_Renderer* t_renderer)
{
	m_bg.render(m_bgX, m_bgY, t_renderer, 1, 1);
	m_botPlay.render(m_playX, m_playY, t_renderer, 1, 1);
	m_localPlay.render(m_localPlayX, m_localPlayY, t_renderer, 1, 1);
	m_onlinePlay.render(m_onlinePlayX, m_onlinePlayY, t_renderer, 1, 1);
	m_Credits.render(m_CreditsX, m_CreditsY, t_renderer, 1, 1);
	m_quitGame.render(m_quitX, m_quitY, t_renderer, 1, 1);
	m_selector.render(m_selectorX, m_selectorY, t_renderer, 1, 1);
}
/// <summary>
/// function that checks controller input and brings user back to the certain gamestate
/// </summary>
/// <returns></returns>
GameStates MenuScene::setNewState()
{
	if (m_controller->m_currentState.A) 
	{
		if (m_selectorY == 150) {
			m_observer->onNotify(AudioObserver::CLICK);
			return GameStates::Game;
		}
		else if (m_selectorY == 250) {
			m_observer->onNotify(AudioObserver::CLICK);
			return GameStates::Hosting;
			
		}
		else if (m_selectorY == 350) {
			m_observer->onNotify(AudioObserver::CLICK);
			return GameStates::Joining;
		}
		else if (m_selectorY == 450) {
			m_observer->onNotify(AudioObserver::CLICK);
			return GameStates::Credits;
		}
		else if (m_selectorY == 550) {
			m_observer->onNotify(AudioObserver::CLICK);
			return GameStates::QuitGame;
		}
	}
	return GameStates::MainMenu;
}
