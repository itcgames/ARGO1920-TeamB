#include "AnimatedSpriteComponent.h"

#include "IdleState.h"
#include "StunnedState.h"
#include "WalkingState.h"
#include "AttackState.h"
#include "InteractState.h"

#include <typeinfo>

AnimatedSpriteComponent::AnimatedSpriteComponent() :
	m_currentState(new IdleState)
{	
	m_currentFrame = 0;
	m_previousState = m_currentState;
}

AnimatedSpriteComponent::AnimatedSpriteComponent(SDL_Texture& t_texture) :
	m_texture(&t_texture),
	m_currentFrame(0),
	m_currentState(new IdleState)
{
	m_previousState = m_currentState;
}

AnimatedSpriteComponent::AnimatedSpriteComponent(const char* t_texture, int t_height, int t_width, int t_noOfFrames,float t_time) :
	m_currentFrame(0),
	m_NoOfFrames(t_noOfFrames),
	m_currentState(new IdleState)
{
	m_previousState = m_currentState;
	m_imageHeight = t_height;
	m_imageWidth = t_width;

	int frameWidth= m_imageWidth;

	SDL_Rect rect;
	rect.h = m_imageHeight;
	rect.w = frameWidth;
	m_surface = IMG_Load(t_texture);

	for (int i = 0; i < m_NoOfFrames; i++)
	{	
		rect.x = frameWidth * i;
		rect.y = 0;
		m_frames.push_back(rect);
	}
	m_time = t_time;	
}  


void AnimatedSpriteComponent::render(int t_posX, int t_posY, float t_angle)
{
	if (m_frames.size() != 0)
	{
		SDL_Rect rendFrame = getFrame(m_currentFrame);
		rendFrame.y = m_frames[m_currentFrame].y;
		rendFrame.x = m_frames[m_currentFrame].x;
		SDL_Rect destRect = { t_posX , t_posY, m_imageWidth, m_imageHeight };
		SDL_Point center = {m_imageWidth / 2, m_imageHeight / 2};
		SDL_RenderCopyEx(m_renderer, m_texture, &rendFrame, &destRect, t_angle, &center, SDL_FLIP_NONE);
	}
}

void AnimatedSpriteComponent::init(SDL_Renderer* t_renderer)
{
	m_renderer = t_renderer;
	m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
	if (!m_texture)
	{
		std::cout << " texture failed to load!" << std::endl;
	}

}

void AnimatedSpriteComponent::update()
{
	if (m_previousState != m_currentState)
	{
		m_previousState = m_currentState;
	}

	m_clock++;
	if (m_clock > m_time)
	{
		if (m_frames.size() > m_currentFrame + 1)
		{
			m_currentFrame++;
		}
		else
		{
			m_currentFrame = 0;
			m_currentState = new IdleState();
		}
		m_clock = 0;
		
	}
}

void AnimatedSpriteComponent::updateSpriteState(SpriteSheet& t_spriteSheet)
{
	m_frames.clear();
	m_currentFrame = 0;

	m_imageHeight = t_spriteSheet.frameSize.x;
	m_imageWidth = t_spriteSheet.frameSize.y;

	int frameWidth = m_imageWidth;

	SDL_Rect rect;
	rect.h = m_imageHeight;
	rect.w = frameWidth;
	m_texture = t_spriteSheet.m_texture;
	m_time = t_spriteSheet.frameRate;

	for (int i = 0; i < m_NoOfFrames; i++)
	{
		rect.x = frameWidth * i;
		rect.y = 0;
		m_frames.push_back(rect);
	}
}

SDL_Rect& AnimatedSpriteComponent::getFrame(int t_f)
{
	return m_frames[t_f];
}

const std::vector<SDL_Rect>& AnimatedSpriteComponent::getFrames()
{
	return m_frames;
}

const int AnimatedSpriteComponent::getCurrentFrame()
{
	return m_currentFrame;
}

void AnimatedSpriteComponent::addFrame(SDL_Rect& t_rect)
{
	m_frames.push_back(t_rect);
}

void AnimatedSpriteComponent::setTexture(SDL_Texture& t_Texture)
{
	m_texture = &t_Texture;
}

void AnimatedSpriteComponent::setRender(SDL_Renderer& t_Renderer)
{
	m_renderer = &t_Renderer;
}

bool AnimatedSpriteComponent::LoadFromFile(const char* t_path)
{
	bool success = true;
	m_surface = IMG_Load(t_path);
	m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
	SDL_FreeSurface(m_surface);

	if (m_texture != NULL)
	{
		success = false;
	}

	return success;
}


int AnimatedSpriteComponent::getWidth()
{
	return m_imageWidth;
}

int AnimatedSpriteComponent::getHeight()
{
	return m_imageHeight;
}

void AnimatedSpriteComponent::setCurrent(State* t_s)
{
	m_currentState = t_s;
}

void AnimatedSpriteComponent::setPrevious(State* t_s)
{
	m_previousState = t_s	;
}

State* AnimatedSpriteComponent::getCurrent()
{
	return m_currentState;
}

State* AnimatedSpriteComponent::getPrevious()
{
	return m_previousState;
}
