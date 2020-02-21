#include "Particle.h"

Particle::Particle(float t_x, float t_y, int t_index,SDL_Renderer * t_renderer, ParticleType t_type):
	m_x(t_x),
	m_y(t_y),
	m_index(t_index),
	m_type(t_type)

{	
	m_position = new PositionComponent(m_x, m_y);
	m_particle = new LTexture();
	m_position->setPosition(m_x, m_y);
	m_particle->loadFromFile("./Assets/fire.png", t_renderer, 3);
	switch (m_type)
	{
	case ParticleType::CheesePickup:
		m_r = rand() % 55 + 200;
		m_g = rand() % 55 + 200;
		m_b = 0;
		m_particle->setColor(m_r, m_g, m_b);
		m_particle->setAlpha(m_alpha);
		m_particle->setScale(3);
		m_lifetime = rand() % 75;	// Make each particle have a random lifetime
		m_velX = 6.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6.0 - 18.1)));
		m_velY = 6.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6.0 - 18.1)));
		break;
	case ParticleType::Test:
		m_r = 20;
		m_g = 255;
		m_b = 255;
		m_particle->setColor(m_r, m_g, m_b);
		m_particle->setAlpha(m_alpha);
		m_particle->setScale(3);
		m_lifetime = rand() % 45;	// Make each particle have a random lifetime
		m_velX = 6.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6.0 - 18.1)));
		m_velY = 6.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6.0 - 18.1)));
	case ParticleType::Dust:
		m_r = 47;
		m_g = 79;
		m_b = 79;
		m_particle->setColor(m_r, m_g, m_b);
		m_particle->setAlpha(m_alpha);
		m_particle->setScale(0.8);
		m_lifetime = rand() % 30;	// Make each particle have a random lifetime
		m_velX = rand() % 1 + (-0.1);
		m_velY = rand() % 1 + (-0.1);
		break;
	default:
		break;

	}


}

void Particle::update()
{
	m_lifetime--;	// Decrements lifetime

	// Sets alpha based on lifetime so particle will slowly fade out
	m_particle->setColor(m_r, m_g, m_b);
	m_particle->setAlpha(m_lifetime);

	// Update position of particle
	m_x += m_velX;
	m_y += m_velY;
	m_position->setPosition(m_x, m_y);
}

void Particle::draw(SDL_Renderer* t_renderer)
{
	m_particle->render(m_x, m_y, t_renderer, 1,1);
}
