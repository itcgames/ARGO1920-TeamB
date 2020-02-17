#ifndef MENU_SCENE_H
#define MENU_SCENE_H
#include <SDL.h>
#include "Enums.h"
class MenuScene
{
	public:
		MenuScene();
		~MenuScene();
	private:
		void playGame();
		void quitGame();
		void playCredits();
		GameStates* m_currentState;
};
#endif // !MENU_SCENE_H

