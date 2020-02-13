#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H


#include"Component.h"
#include"SDL_image.h"
class RenderComponent : public Component {
public:
	RenderComponent(const char* name, int width, int height, SDL_Renderer* renderer);
	void draw(int x, int y, double t_angle = 0);
	void setImage(const char* name);
	void setAngle(double t_angle) { m_angle = t_angle; }
private:
	double m_angle;
	SDL_Renderer* m_renderer;

	SDL_Surface* image;
	SDL_Texture* texture;
	SDL_Rect srcrect;
	SDL_Rect dstrect;

	int width;
	int height;
	const char* currentImage;
};

#endif // !RENDERCOMPONENT_H

