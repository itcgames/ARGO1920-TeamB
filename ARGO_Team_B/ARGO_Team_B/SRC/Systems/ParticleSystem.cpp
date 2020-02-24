#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(int count, float t_x, float t_y, SDL_Renderer* t_renderer, ParticleType t_type):
	m_x(t_x),
	m_y(t_y)
{
	for (int i = 0; i < count; i++) {
		// Loop that will reiterate for each desired particle
			// Add a new particle to the particle system
		m_particles.push_back(new Particle(m_x, m_y, i,t_renderer,t_type));
	}
}

void ParticleSystem::update()
{
	for (int i = 0; i < m_particles.size(); i++) {
		// Loops through every particle
		m_particles.at(i)->update();	// Updates particle
		if (m_particles.at(i)->m_lifetime < 0) {
			// checks if particle is dead
			m_particles.erase(m_particles.begin() + i);	// Deletes particle
		}
	}
}

void ParticleSystem::draw(SDL_Renderer* t_renderer)
{
	for (Particle* p : m_particles) {
		// Loops through every particle 
		p->draw(t_renderer);
	}
}

void ParticleSystem::resetParticle(int index, SDL_Renderer* t_renderer, ParticleType t_type)
{
	// Sets dead particle to a new particle
	m_particles.at(index) = new Particle(m_x,m_y, index,t_renderer,t_type);
}
