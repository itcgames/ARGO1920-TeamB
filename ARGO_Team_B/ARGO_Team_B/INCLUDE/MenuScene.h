#ifndef MENU_SCENE_H
#define MENU_SCENE_H
#include <SDL.h>
#include "Enums.h"
#include <SDL_image.h>
#include <SDL.h>
#include <string>
#include "GUIElement.h"
#include <iostream>
class MenuScene
{
	public:
		MenuScene(SDL_Renderer* t_renderer,GameStates * t_state);
		~MenuScene();
		void update(float dt);
		void render(SDL_Renderer* t_renderer);

	private:
		void playGame();
		void quitGame();
		void playCredits();
		GameStates* m_currentState;
		GUIElement m_localPlayTexture;
		GUIElement m_onlinePlayTexture;
		GUIElement m_botPlayTexture;
		GUIElement m_creditsTexture;
		GUIElement m_quitGameTexture;

};
#endif // !MENU_SCENE_H

