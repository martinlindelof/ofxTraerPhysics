#include "RungeKuttaIntegrator.h"

namespace traer { namespace physics {

	//--------------------------------------------------------------
	RungeKuttaIntegrator::RungeKuttaIntegrator( ParticleSystem* system )
	{
		s = system;
	}

	//--------------------------------------------------------------
	RungeKuttaIntegrator::~RungeKuttaIntegrator(){

	}
	
	//--------------------------------------------------------------
	void RungeKuttaIntegrator::allocateParticles()
	{
		while ( s->particles.size() > originalPositions.size() )
		{
			originalPositions.push_back( ofVec3f() );
			originalVelocities.push_back( ofVec3f() );
			k1Forces.push_back( ofVec3f() );
			k1Velocities.push_back( ofVec3f() );
			k2Forces.push_back( ofVec3f() );
			k2Velocities.push_back( ofVec3f() );
			k3Forces.push_back( ofVec3f() );
			k3Velocities.push_back( ofVec3f() );
			k4Forces.push_back( ofVec3f() );
			k4Velocities.push_back( ofVec3f() );
		}
	}
	
	//--------------------------------------------------------------
	void RungeKuttaIntegrator::step( const float &deltaT )
	{	
		allocateParticles();
		/////////////////////////////////////////////////////////
		// save original position and velocities
		
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle* p = s->particles[i];
			if ( !p->fixed )
			{		
				originalPositions[i].set( p->position );
				originalVelocities[i].set( p->velocity );
			}
			
			p->force.set(0,0,0);	// and clear the forces
		}
		
		////////////////////////////////////////////////////////
		// get all the k1 values
		
		s->applyForces();
		
		// save the intermediate forces
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle* p = s->particles[i];
			if ( !p->fixed )
			{
				k1Forces[i].set( p->force );
				k1Velocities[i].set( p->velocity );                
			}
			
			p->force.set(0,0,0);	// and clear the forces
		}
		
		////////////////////////////////////////////////////////////////
		// get k2 values
		
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle* p = s->particles[i];
			if ( !p->fixed )
			{
				ofVec3f originalPosition = originalPositions[i];
				ofVec3f k1Velocity = k1Velocities[i];
				
                p->position.set( originalPosition + (k1Velocity * (0.5f * deltaT)) );
				
				ofVec3f originalVelocity = originalVelocities[i];
				ofVec3f k1Force = k1Forces[i];

				p->velocity.set( originalVelocity + k1Force * 0.5f * deltaT / p->mass );
			}
		}
		
		s->applyForces();

		// save the intermediate forces
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle* p = s->particles[i];
			if ( !p->fixed )
			{
				k2Forces[i].set( p->force );
				k2Velocities[i].set( p->velocity );                
			}
			
			p->force.set(0,0,0);	// and clear the forces now that we are done with them
		}
		
		
		/////////////////////////////////////////////////////
		// get k3 values
		
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle* p = s->particles[i];
			if ( !p->fixed )
			{
                ofVec3f originalPosition = originalPositions[i];
                ofVec3f k2Velocity = k2Velocities[i];
				
                p->position.set( originalPosition + k2Velocity * 0.5f * deltaT );
				
                ofVec3f originalVelocity = originalVelocities[i];
                ofVec3f k2Force = k2Forces[i];

                p->velocity.set( originalVelocity + k2Force * 0.5f * deltaT / p->mass );
			}
		}
        
		s->applyForces();
		
		// save the intermediate forces
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle* p = s->particles[i];
			if ( !p->fixed )
			{
				k3Forces[i].set( p->force );
				k3Velocities[i].set( p->velocity );                
			}
			
			p->force.set(0,0,0);	// and clear the forces now that we are done with them
		}
		
		
		//////////////////////////////////////////////////
		// get k4 values
		
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle* p = s->particles[i];
			if ( !p->fixed )
			{
                ofVec3f originalPosition = originalPositions[i];
				ofVec3f k3Velocity = k3Velocities[i];
				
				p->position.set( originalPosition + k3Velocity * deltaT);
				
				ofVec3f originalVelocity = originalVelocities[i];
				ofVec3f k3Force = k3Forces[i];

				p->velocity.set( originalVelocity + k3Force * deltaT / p->mass );
			}
		}
		
		s->applyForces();

		// save the intermediate forces
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle* p = s->particles[i];
			if ( !p->fixed )
			{
				k4Forces[i].set( p->force );
				k4Velocities[i].set( p->velocity );                
			}			
		}
		
		
		/////////////////////////////////////////////////////////////
		// put them all together and what do you get?
		
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle* p = s->particles[i];
            p->age += deltaT;
			if ( !p->fixed )
			{
				// update position
				
                ofVec3f originalPosition = originalPositions[i];
				ofVec3f k1Velocity = k1Velocities[i];
				ofVec3f k2Velocity = k2Velocities[i];
				ofVec3f k3Velocity = k3Velocities[i];
				ofVec3f k4Velocity = k4Velocities[i];
				
				p->position.set( originalPosition + deltaT / 6.0f * ( k1Velocity + 2.0f*k2Velocity + 2.0f*k3Velocity + k4Velocity ) );
				
				// update velocity
				
                ofVec3f originalVelocity = originalVelocities[i];
				ofVec3f k1Force = k1Forces[i];
				ofVec3f k2Force = k2Forces[i];
				ofVec3f k3Force = k3Forces[i];
				ofVec3f k4Force = k4Forces[i];
				
                p->velocity.set( originalVelocity + deltaT / ( 6.0f * p->mass ) * ( k1Force + 2.0f*k2Force + 2.0f*k3Force + k4Force ) );
			}
		}
	}

} } // namespace traer::physics