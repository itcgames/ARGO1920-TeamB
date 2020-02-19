#pragma once
#include <iostream>
#include "SDL.h"
#include "LTexture.h"
#include "PositionComponent.h"
enum ParticleType
{
	CheesePickup,
	Test
};
class Particle
{
public:
	// Constructor
	Particle(float t_x,float t_y, int t_index, SDL_Renderer* t_renderer,ParticleType t_type);

	// Update and render functions
	void update();
	void draw(SDL_Renderer * t_renderer);

	int m_lifetime;	// How long the particle will be alive for
	int m_index;	// The particles index in the particle system

private:
	PositionComponent* m_position;
	// Physical attributes of the particle
	float m_x, m_y, m_velX, m_velY;
	int m_r;
	int m_g;
	int m_b;
	int m_alpha = 255;
	LTexture* m_particle = NULL;
	ParticleType m_type;
};