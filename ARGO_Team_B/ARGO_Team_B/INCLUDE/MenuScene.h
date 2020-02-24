#ifndef MENU_SCENE_H
#define MENU_SCENE_H
#include <SDL.h>
#include "Enums.h"
#include <SDL_image.h>

#include <iostream>
#include "ControlComponent.h"
#include "Xbox360Controller.h"


class MenuScene
{
public:
	MenuScene(SDL_Renderer * t_renderer,GameStates * t_gamestate, ControlComponent* t_control);
	~MenuScene();
	void handleEvents();
	void update(float dt);
	void render(SDL_Renderer* t_renderer);
	GameStates setNewState();
private:
	//current game state
	GameStates* m_currentState;
	//x , y , width and height of menu buttons,selector  and menu background
	int m_playX, m_playY, m_playW, m_playH;
	int m_localPlayX, m_localPlayY, m_localPlayW, m_localPlayH;
	int m_onlinePlayX, m_onlinePlayY, m_onlinePlayW, m_onlinePlayH;
	int m_CreditsX, m_CreditsY, m_CreditsW, m_CreditsH;
	int m_bgX, m_bgY, m_bgW, m_bgH;
	int m_quitX, m_quitY, m_quitW, m_quitH;
	int m_selectorX, m_selectorY, m_selectorW, m_selectorH;

	// Bot Play button
	LTexture m_botPlay;

	// Local Play button
	LTexture m_localPlay;

	// Online Play button
	LTexture m_onlinePlay;

	// Quit Game button
	LTexture m_quitGame;

	// Credits button
	LTexture m_Credits;

	// Credits button
	LTexture m_selector;

	//background Image
	LTexture m_bg;

	//timer and offset for clicking of button
	float m_buttomTimer;
	float m_timerOffset;
	//audio observer
	AudioObserver* m_observer;
	//xbox controller for input
	Xbox360Controller* m_controller;
};
#endif // !MENU_SCENE_H