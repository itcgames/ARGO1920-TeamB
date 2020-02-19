#ifndef GAME_SCENE_H
#define GAME_SCENE_H
#include <SDL.h>
class GameScene
{
public:
	GameScene(SDL_Renderer* t_renderer);
	~GameScene();
	void update(float dt);
	void render(SDL_Renderer* t_renderer);
private:

	
};
#endif // !MENU_SCENE_H

