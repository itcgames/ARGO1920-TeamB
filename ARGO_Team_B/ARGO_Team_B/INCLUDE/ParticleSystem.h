#include "Particle.h"
#include <vector>
class ParticleSystem
{
public:

	ParticleSystem(int count, float t_x,float t_y, SDL_Renderer* t_renderer, ParticleType t_type);	// Constructor

	// Update and draw functions
	void update();
	void draw(SDL_Renderer * t_renderer);

	std::vector<Particle*> m_particles;	// The vector particles the system handles

private:

	void resetParticle(int index, SDL_Renderer* t_renderer, ParticleType t_type);	// Function to reset particle when particle is dead

	float m_x, m_y;
};