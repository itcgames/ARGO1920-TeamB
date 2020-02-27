#ifndef CREDITS_SCENE_H
#define CREDITS_SCENE_H
#include <SDL.h>
#include "Enums.h"
#include "ControlComponent.h"
#include "Xbox360Controller.h"
class CreditsScene
{
	public:
		CreditsScene(SDL_Renderer* t_renderer, GameStates* t_state,ControlComponent* t_control);
		~CreditsScene();
		void update(float dt);
		void render(SDL_Renderer* t_renderer);
		GameStates backToMenu();
	private:

		//current game state
		GameStates* m_currentState;
		// Credits Screen texture
		LTexture m_creditsScreen;
		//x , y , width and height of credits background
		int m_creditsX, m_creditsY, m_creditsW, m_creditsH;
		
		//timer and offset for clicking of button
		float m_buttomTimer;
		float m_timerOffset;
		//audio observer
		AudioObserver* m_observer;
		//xbox controller for input
		Xbox360Controller* m_controller;
};
#endif // !CREDITS_SCENE_H

