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

AnimatedSpriteComponent::AnimatedSpriteComponent(const char* t_texture, int t_height, int t_width, int t_noOfFrames, SDL_Renderer* t_renderer) :
	m_currentFrame(0),
	m_NoOfFrames(t_noOfFrames),
	m_renderer(t_renderer)
{
	m_imageHeight = t_height;
	m_imageWidth = t_width;

	int frameWidth= m_imageWidth / t_noOfFrames;

	SDL_Rect rect;
	rect.h = m_imageHeight;
	rect.w = frameWidth;
	m_surface = IMG_Load(t_texture);
	m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);

	for (int i = 0; i < m_NoOfFrames; i++)
	{
		
		rect.x = frameWidth * i;
		rect.y = 0;
		m_frames.push_back(rect);
	}
	
}


void AnimatedSpriteComponent::render(int t_posX, int t_posY)
{
	SDL_Rect rendFrame = getFrame(m_currentFrame);
	rendFrame.y = m_frames[m_currentFrame].y;
	rendFrame.x = m_frames[m_currentFrame].x;
	SDL_Rect destRect = { t_posX, t_posY, m_imageWidth / m_NoOfFrames, m_imageHeight};
	SDL_RenderCopy(m_renderer, m_texture, &rendFrame, &destRect);
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
	return m_imageWidth;
}

int AnimatedSpriteComponent::getHeight()
{
	return m_imageHeight;
}
