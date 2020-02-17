#include "MenuScene.h"

MenuScene::MenuScene(SDL_Renderer* t_renderer, GameStates* t_state):
	m_currentState(t_state),
	m_localPlayTexture("./Assets/menu/localPlay.png", 500, 500, 400, 100)
{
	// Initialise SDL_IMG
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		std::cout << "Failed to initialise IMG" << std::endl;
	}
	;
}

MenuScene::~MenuScene()
{
}

void MenuScene::update(float dt)
{
}

void MenuScene::render(SDL_Renderer* t_renderer)
{
	m_localPlayTexture.render(t_renderer);
}

void MenuScene::playGame()
{
}

void MenuScene::quitGame()
{
}

void MenuScene::playCredits()
{
}