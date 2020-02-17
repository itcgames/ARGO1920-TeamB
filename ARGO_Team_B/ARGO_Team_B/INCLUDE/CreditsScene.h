#ifndef CREDITS_SCENE_H
#define CREDITS_SCENE_H
#include <SDL.h>
#include "Enums.h"
class CreditsScene
{
	public:
		CreditsScene(SDL_Renderer* t_renderer, GameStates* t_state);
		~CreditsScene();
		void update(float dt);
		void render(SDL_Renderer* t_renderer);
	private:
		void backToMenu();
		GameStates* m_currentState;
};
#endif // !CREDITS_SCENE_H

