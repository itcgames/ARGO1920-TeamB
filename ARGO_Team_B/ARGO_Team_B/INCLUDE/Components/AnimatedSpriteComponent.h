#pragma once

#include "Component.h"
#include "Enums.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
class AnimatedSpriteComponent : public Component
{
private:
	class State* m_current;

	SDL_Texture* m_texture;
	SDL_Surface* m_surface;
	int m_imageHeight;
	int m_imageWidth;
	SDL_Renderer* m_renderer = nullptr;
	SDL_Rect m_intRect{ 0,0,75,32 };
	std::vector<SDL_Rect> m_frames;
	int m_NoOfFrames{ 0 };
	int m_currentFrame;
	float m_time{ 8000 };
	int m_clock;

public:
	AnimatedSpriteComponent();
	AnimatedSpriteComponent(SDL_Texture& t_texture);
	AnimatedSpriteComponent(const char* t_texture, int t_height, int t_width, int t_noOfFrames, SDL_Renderer* t_renderer);
	void update();
	SDL_Rect& getFrame(int t_f);
	const std::vector<SDL_Rect>& getFrames();
	const int getCurrentFrame();
	void addFrame(SDL_Rect& t_rect);
	void setTexture(SDL_Texture& t_Texture);
	void setRender(SDL_Renderer& t_Renderer);
	bool LoadFromFile(const char* t_path);
	void render(int t_posX, int t_posY);
	int getWidth();
	int getHeight();

	/// <summary>
	/// States Information
	/// </summary>
	void setCurrent(State* t_s);
	void idle();
	void walking();
	void stunned();
	void attack();
	void interact();

	//void setprevious(State* t_s);
	//State* getCurrent();
	//State* getPrevious();
};
