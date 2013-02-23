// #include "cinder/Vector.h"
#include "ModifiedEulerIntegrator.h"

namespace traer { namespace physics {

	ModifiedEulerIntegrator::ModifiedEulerIntegrator( ParticleSystem *system )
	{
		s = system;
	}
	
	void ModifiedEulerIntegrator::step( const float &t )
	{
		s->clearForces();
		s->applyForces();
		
		const float halftt = 0.5f*t*t;
		
		for ( int i = 0; i < s->numberOfParticles(); i++ )
		{
			Particle* p = s->getParticle( i );
			if ( !p->fixed )
			{
                // const ci::Vec3f a = p->force / p->mass;				
                const ofVec3f a = p->force / p->mass;
                p->position += p->velocity/t;
                p->position += a * halftt;
                p->velocity += a / t;
			}
		}
	}

} } // namespace traer::physics