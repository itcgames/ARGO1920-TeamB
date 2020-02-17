#ifndef MENU_SCENE_H
#define MENU_SCENE_H
#include <SDL.h>
#include "Enums.h"
#include <SDL_image.h>
#include <SDL.h>
#include <string>

#include <iostream>
#include "LTexture.h"
class MenuScene
{
	public:
		MenuScene(SDL_Renderer* t_renderer,GameStates * t_state);
		~MenuScene();
		void init();
		void update(float dt);
		void render(SDL_Renderer* t_renderer);
		
	private:
		GameStates* m_currentState;
		int m_playX, m_playY, m_playW, m_playH;
		int m_localPlayX, m_localPlayY, m_localPlayW, m_localPlayH;
		int m_onlinePlayX, m_onlinePlayY, m_onlinePlayW, m_onlinePlayH;
		int m_CreditsX, m_CreditsY, m_CreditsW, m_CreditsH;
		int m_bgX, m_bgY, m_bgW, m_bgH;
		int m_quitX, m_quitY, m_quitW, m_quitH;
		int m_titleX, m_titleY;

		//Title button
		LTexture m_title;

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

		//background Image
		LTexture m_bg;

};
#endif // !MENU_SCENE_H

