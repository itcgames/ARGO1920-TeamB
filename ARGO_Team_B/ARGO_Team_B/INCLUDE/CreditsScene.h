#ifndef CREDITS_SCENE_H
#define CREDITS_SCENE_H
#include <SDL.h>
#include "Enums.h"
class CreditsScene
{
public:
	CreditsScene();
	~CreditsScene();
private:
	GameStates* m_currentState;
};
#endif // !CREDITS_SCENE_H

