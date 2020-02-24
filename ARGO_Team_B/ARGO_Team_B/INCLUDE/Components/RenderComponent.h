#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H


#include"Component.h"
#include"SDL_image.h"
class RenderComponent : public Component {
public:
	RenderComponent(const char* name, int width, int height,int imgWidth,int imgHeight, SDL_Renderer* renderer);
	void draw(int x, int y);
	void draw(int x, int y, double angle);
	void draw(int x, int y, double angle, Uint8 alpha);
	void draw(int x, int y, double angle, int width, int height);
	void setImage(const char* name);
	void setImage(const char* name, int width, int height);
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
	SDL_Point center;
	const char* currentImage;
};

#endif // !RENDERCOMPONENT_H

