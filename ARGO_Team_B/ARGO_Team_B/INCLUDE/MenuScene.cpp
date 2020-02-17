#include "MenuScene.h"

MenuScene::MenuScene(SDL_Renderer* t_renderer, GameStates* t_state):
	m_currentState(t_state)
	
{
	if (!m_bg.loadFromFile("./Assets/menu/backgroundImage.png", t_renderer, 1))
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
	m_playX = 50;
	m_playY = 150;
	m_playW = m_botPlay.getWidth();
	m_playH = m_botPlay.getHeight();

	if (!m_localPlay.loadFromFile("./Assets/menu/localPlay.png", t_renderer, 1))
	{
		printf("Failed to load play texture!\n");
	}
	m_localPlayX = 50;
	m_localPlayY = 250;
	m_localPlayW = m_localPlay.getWidth();
	m_localPlayH = m_localPlay.getHeight();

	if (!m_onlinePlay.loadFromFile("./Assets/menu/onlinePlay.png", t_renderer, 1))
	{
		printf("Failed to load play texture!\n");
	}
	m_onlinePlayX = 50;
	m_onlinePlayY = 350;
	m_onlinePlayW = m_onlinePlay.getWidth();
	m_onlinePlayH = m_onlinePlay.getHeight();

	if (!m_Credits.loadFromFile("./Assets/menu/credits.png", t_renderer, 1))
	{
		printf("Failed to load play texture!\n");
	}
	m_CreditsX = 50;
	m_CreditsY = 450;
	m_CreditsW = m_Credits.getWidth();
	m_CreditsH = m_Credits.getHeight();

	if (!m_quitGame.loadFromFile("./Assets/menu/quitGame.png", t_renderer, 1))
	{
		printf("Failed to load play texture!\n");
	}
	m_quitX = 50;
	m_quitY = 550;
	m_quitW = m_quitGame.getWidth();
	m_quitH = m_quitGame.getHeight();



}

MenuScene::~MenuScene()
{
}

void MenuScene::init()
{
}

void MenuScene::update(float dt)
{
}

void MenuScene::render(SDL_Renderer* t_renderer)
{
	m_bg.render(m_bgX, m_bgY, t_renderer, 1, 1);
	m_botPlay.render(m_playX, m_playY, t_renderer, 1, 1);
	m_localPlay.render(m_localPlayX, m_localPlayY, t_renderer, 1, 1);
	m_onlinePlay.render(m_onlinePlayX, m_onlinePlayY, t_renderer, 1, 1);
	m_Credits.render(m_CreditsX, m_CreditsY, t_renderer, 1, 1);
	m_quitGame.render(m_playX, m_quitY, t_renderer, 1, 1);
}