#pragma once

#include"Component.h"
#include"SDL_image.h"
class RenderComponent : public Component {
public:
	RenderComponent(const char* name, int width, int height, SDL_Renderer* renderer);
	void draw(int x, int y);
private:
	SDL_Renderer* m_renderer;

	SDL_Surface* image;
	SDL_Texture* texture;
	SDL_Rect srcrect;
	SDL_Rect dstrect;

	int width;
	int height;
};



