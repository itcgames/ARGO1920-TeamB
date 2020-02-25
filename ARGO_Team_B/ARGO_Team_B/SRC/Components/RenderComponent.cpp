#include "RenderComponent.h"
#include<iostream>

RenderComponent::RenderComponent(const char* name, int width, int height, int imgWidth, int imgHeight) :
	m_angle{ 0 },
	currentImage(name)
{
	m_image = IMG_Load(name);

	this->width = width;
	this->height = height;
	srcrect = { 0, 0, imgWidth, imgHeight };
	dstrect = { 0, 0, this->width, this->height };
	//center = { 0, 0 };
}

void RenderComponent::init(SDL_Renderer* renderer)
{
	m_renderer = renderer;
	texture = SDL_CreateTextureFromSurface(m_renderer, m_image);
	if (!texture)
	{
		std::cout << " texture failed to load!" << std::endl;
	}
}

void RenderComponent::draw(int x, int y)
{
	dstrect = { x - this->width / 2, y - this->height / 2, this->width, this->height };
	//center = { x + this->width / 2, y + this->height / 2 };
	SDL_RenderCopyEx(m_renderer, texture, &srcrect, &dstrect, 0, NULL, SDL_FLIP_NONE);
}

void RenderComponent::draw(int x, int y, double angle)
{
	dstrect = { x, y, this->width, this->height };
	//center = { x + this->width / 2, y + this->height / 2 };
	SDL_RenderCopyEx(m_renderer, texture, &srcrect, &dstrect, angle, NULL, SDL_FLIP_NONE);
}

void RenderComponent::draw(int x, int y, double angle, int width, int height)
{
	dstrect = { x, y, width, height };
	//center = { x + this->width / 2, y + this->height / 2 };
	SDL_RenderCopyEx(m_renderer, texture, &srcrect, &dstrect, angle, NULL, SDL_FLIP_NONE);
}

void RenderComponent::draw(int x, int y, double angle, Uint8 alpha)
{
	dstrect = { x, y, this->width, this->height };
	//center = { x + this->width / 2, y + this->height / 2 };
	SDL_SetTextureAlphaMod(texture, alpha);
	SDL_RenderCopyEx(m_renderer, texture, &srcrect, &dstrect, angle, NULL, SDL_FLIP_NONE);
}

void RenderComponent::setImage(const char* name)
{
	if (currentImage != name) {
		currentImage = name;
		m_image = IMG_Load(name);
		texture = SDL_CreateTextureFromSurface(m_renderer, m_image);

		if (!texture)
		{
			std::cout << name << " texture failed to load!" << std::endl;
		}
	}
}

void RenderComponent::setImage(const char* name, int width, int height)
{
	if (currentImage != name) {
		this->width = width;
		this->height = height;
		srcrect = { 0, 0, width , height };

		currentImage = name;
		m_image = IMG_Load(name);
		texture = SDL_CreateTextureFromSurface(m_renderer, m_image);

		if (!texture)
		{
			std::cout << name << " texture failed to load!" << std::endl;
		}
	}
}