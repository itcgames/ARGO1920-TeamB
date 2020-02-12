#include "RenderComponent.h"
#include<iostream>

RenderComponent::RenderComponent(const char* name, int width, int height, SDL_Renderer* renderer)
{
	this->width = width;
	this->height = height;
	srcrect = { 0, 0, this->width, this->height };
	dstrect = { 0, 0, this->width, this->height };
	m_renderer = renderer;
	image = IMG_Load(name);
	texture = SDL_CreateTextureFromSurface(m_renderer, image);

	if (!texture)
	{
		std::cout << name << " texture failed to load!" << std::endl;
	}
}

void RenderComponent::draw(int x, int y)
{
	dstrect = { x, y, this->width, this->height };
	SDL_RenderCopy(m_renderer, texture, &srcrect, &dstrect);
}
