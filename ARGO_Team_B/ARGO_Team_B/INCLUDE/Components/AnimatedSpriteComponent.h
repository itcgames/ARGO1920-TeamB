#pragma once

#include "Component.h"
#include "Enums.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

struct SpriteSheet
{
	const char* name;
	SDL_Texture* m_texture = NULL;
	SDL_Point frameSize{ 0,0 };
	int t_noOfFrames;
	float frameRate;

};

class AnimatedSpriteComponent : public Component
{
private:
	
	class State* m_previousState;
	class State* m_currentState;

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
	AnimatedSpriteComponent(const char* t_texture, int t_height, int t_width, int t_noOfFrames, float t_time);
	
	void init(SDL_Renderer* t_renderer);
	void update();

	void updateSpriteState(SpriteSheet& t_spriteSheet);

	SDL_Rect& getFrame(int t_f);
	const std::vector<SDL_Rect>& getFrames();
	const int getCurrentFrame();
	void addFrame(SDL_Rect& t_rect);
	void setTexture(SDL_Texture& t_Texture);
	void setRender(SDL_Renderer& t_Renderer);
	bool LoadFromFile(const char* t_path);
	void render(int t_posX, int t_posY, float t_angle);
	int getWidth();
	int getHeight();

	/// <summary>
	/// States Information
	/// </summary>


	void setCurrent(State* t_s);
	void setPrevious(State* t_s);
	
	State* getCurrent();
	State* getPrevious();



};
