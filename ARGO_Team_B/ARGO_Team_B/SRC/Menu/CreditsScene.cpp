#include "CreditsScene.h"

/// <summary>
/// overloaded constructor for the credits scene
/// set up the background texture and audio observer
/// </summary>
/// <param name="t_renderer"></param>
/// <param name="t_state"></param>
/// <param name="t_control"></param>
CreditsScene::CreditsScene(SDL_Renderer* t_renderer, GameStates* t_state, ControlComponent* t_control):
	m_currentState(t_state),
	m_buttomTimer(0.0f),
	m_timerOffset(1.0f)
{

	if (!m_creditsScreen.loadFromFile("./Assets/menu/creditsScreen.png", t_renderer, 1))
	{
		printf("Failed to load BG texture!\n");
	}
	m_creditsX = 0;
	m_creditsY = 0;
	m_creditsW = m_creditsScreen.getWidth();
	m_creditsH = m_creditsScreen.getHeight();
	m_controller = t_control->getController();

	m_observer = new AudioObserver();
	m_observer->load();
	m_observer->StartBGM(2);
}

/// <summary>
/// credits scene destructor
/// </summary>
CreditsScene::~CreditsScene()
{
}

/// <summary>
/// update the button timer, so it doesnt repeat itself when pressed
/// </summary>
/// <param name="dt"></param>
void CreditsScene::update(float dt)
{
	if (m_buttomTimer > 0.0f) 
	{
		m_buttomTimer -= dt;
	}
}

/// <summary>
/// render the credits background texture
/// </summary>
/// <param name="t_renderer"></param>
void CreditsScene::render(SDL_Renderer* t_renderer)
{
	m_creditsScreen.render(m_creditsX, m_creditsY, t_renderer, 1, 1);
}

/// <summary>
/// function that checks controller input and brings user back to the main menu
/// </summary>
/// <returns></returns>
GameStates CreditsScene::backToMenu()
{
	m_controller->checkButton();
	if (m_controller->m_currentState.B)
	{
		m_observer->onNotify(AudioObserver::CLICK);
		return GameStates::MainMenu;
	}
	return GameStates::Credits;
}