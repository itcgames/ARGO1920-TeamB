#include "..\INCLUDE\AnimatedSpriteComponent.h"

AnimatedSpriteComponent::AnimatedSpriteComponent()
{	
	m_currentFrame = 0;
}

AnimatedSpriteComponent::AnimatedSpriteComponent(SDL_Texture& t_texture) :
	m_texture(&t_texture),
	m_currentFrame(0)
{

}

AnimatedSpriteComponent::AnimatedSpriteComponent(SDL_Texture& t_texture, const SDL_Rect& t_rect) :
	m_texture(&t_texture),
	m_currentFrame(0)
{
	m_frames.push_back(t_rect);
}

void AnimatedSpriteComponent::update()
{
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
		}
		m_clock = 0;
	}
}

const int& AnimatedSpriteComponent::getClock()
{
	return m_clock;
}

const float& AnimatedSpriteComponent::getTime()
{
	return m_time;
}

SDL_Rect& AnimatedSpriteComponent::getFrame(int t_f)
{
	return m_frames[t_f];
}

const std::vector<SDL_Rect>& AnimatedSpriteComponent::getFrames()
{
	return m_frames;
}

const SDL_Rect& AnimatedSpriteComponent::getIntRect()
{
	return m_intRect;
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
	return 0;
}

int AnimatedSpriteComponent::getHeight()
{
	return 0;
}
