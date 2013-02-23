/*
 * May 29, 2005
 */
 
#include "ParticleSystem.h"
#include "ModifiedEulerIntegrator.h"
// #include "EulerIntegrator.h"
 
namespace traer { namespace physics {

    //--------------------------------------------------------------
    void ParticleSystem::setIntegrator( Integrator *i )
    {
        delete integrator;
        integrator = i;
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::setGravity( float x, float y, float z )
    {
        gravity.set( x, y, z );
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::setGravity( float g )
    {
        // default down gravity
        gravity.set( 0, g, 0 );
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::setDrag( float d )
    {
        drag = d;
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::tick()
    {
        tick( 1 );
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::tick( float t )
    {  
        integrator->step( t );
    }
    
    //--------------------------------------------------------------
    Particle* ParticleSystem::makeParticle( float mass, float x, float y, float z )
    {
        Particle* p = new Particle( mass );
        p->position.set(x, y, z);
        particles.push_back( p );
        return p;
    }
    
    //--------------------------------------------------------------
    Particle* ParticleSystem::makeParticle()
    {  
        return makeParticle( 1.0f, 0.0f, 0.0f, 0.0f );
    }

    //--------------------------------------------------------------
    Particle* ParticleSystem::makeParticle( float mass, ofPoint p){
    
        return makeParticle( mass, p.x, p.y, p.z);        
    
    };
    
    //--------------------------------------------------------------
    Spring* ParticleSystem::makeSpring( Particle* a, Particle* b, float ks, float d, float r )
    {
        Spring* s = new Spring( a, b, ks, d, r );
        springs.push_back( s );
        return s;
    }
    
    //--------------------------------------------------------------
    Attraction* ParticleSystem::makeAttraction( Particle* a, Particle* b, float k, float minDistance )
    {
        Attraction* m = new Attraction( a, b, k, minDistance );
        attractions.push_back( m );
        return m;
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::clear()
    {
        for (int i = 0; i < particles.size(); i++) {
            delete particles[i];
        }
        for (int i = 0; i < springs.size(); i++) {
            delete springs[i];
        }
        for (int i = 0; i < attractions.size(); i++) {
            delete attractions[i];
        }
        for (int i = 0; i < customForces.size(); i++) {
            delete customForces[i];
        }
        particles.clear();
        springs.clear();
        attractions.clear();
        customForces.clear();
    }

    //--------------------------------------------------------------
    ParticleSystem::ParticleSystem( float g, float somedrag )
    {
        integrator = new ModifiedEulerIntegrator( this );
        gravity.set( 0, g, 0 );
        drag = somedrag;
    }
    
    //--------------------------------------------------------------
    ParticleSystem::ParticleSystem( float gx, float gy, float gz, float somedrag )
    {
        integrator = new ModifiedEulerIntegrator( this );
        gravity.set( gx, gy, gz );
        drag = somedrag;
    }
    
    //--------------------------------------------------------------
    ParticleSystem::ParticleSystem()
    {
        integrator = new ModifiedEulerIntegrator( this );
        gravity.set( 0, DEFAULT_GRAVITY, 0 );
        drag = DEFAULT_DRAG;
    }

    //--------------------------------------------------------------
    ParticleSystem::~ParticleSystem(){
        
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::applyForces()
    {
        if ( gravity.length() > 0.0f )
        {
            for ( int i = 0; i < particles.size(); ++i )
            {
                Particle* p = particles[i];
                p->force += gravity;
            }
        }
        
        for ( int i = 0; i < particles.size(); ++i )
        {
            Particle* p = particles[i];
            p->force -= p->velocity * drag;
        }
        
        for ( int i = 0; i < springs.size(); i++ )
        {
            Spring* f = springs[i];
            f->apply();
        }
        
        for ( int i = 0; i < attractions.size(); i++ )
        {
            Attraction* f = attractions[i];
            f->apply();
        }
        
        for ( int i = 0; i < customForces.size(); i++ )
        {
            Force* f = customForces[i];
            f->apply();
        }
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::clearForces()
    {
        for ( int i = 0; i < particles.size(); ++i )
        {
            Particle* p = particles[i];
            p->force.set(0,0,0);
        }
    }
    
    //--------------------------------------------------------------
    int ParticleSystem::numberOfParticles()
    {
        return particles.size();
    }
    
    //--------------------------------------------------------------
    int ParticleSystem::numberOfSprings()
    {
        return springs.size();
    }
    
    //--------------------------------------------------------------
    int ParticleSystem::numberOfAttractions()
    {
        return attractions.size();
    }
    
    //--------------------------------------------------------------
    Particle* ParticleSystem::getParticle( int i )
    {
        return particles[i];
    }
    
    //--------------------------------------------------------------
    Spring* ParticleSystem::getSpring( int i )
    {
        return springs[i];
    }
    
    //--------------------------------------------------------------
    Attraction* ParticleSystem::getAttraction( int i )
    {
        return attractions[i];
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::addCustomForce( Force* f )
    {
        customForces.push_back( f );
    }
    
    //--------------------------------------------------------------
    int ParticleSystem::numberOfCustomForces()
    {
        return customForces.size();
    }
    
    //--------------------------------------------------------------
    Force* ParticleSystem::getCustomForce( int i )
    {
        return customForces[i];
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::removeCustomForce( int i )
    {
        Force* erased = customForces[i];
        customForces.erase( customForces.begin() + i );
        delete erased;
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::removeParticle( Particle* p )
    {
        particles.erase( std::find(particles.begin(), particles.end(), p) );
        delete p;
    }

    //--------------------------------------------------------------
    void ParticleSystem::removeParticle( int i )
    {
        Particle* erased = particles[i];
        particles.erase( particles.begin() + i );
        delete erased;
    }    
    
    //--------------------------------------------------------------
    void ParticleSystem::removeSpring( int i )
    {
        Spring* erased = springs[i];
        springs.erase( springs.begin() + i );
        delete erased;
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::removeAttraction( int i  )
    {
        Attraction* erased = attractions[i];
        attractions.erase( attractions.begin() + i );
        delete erased;
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::removeAttraction( Attraction* s )
    {
        attractions.erase( std::find(attractions.begin(), attractions.end(), s) );
        delete s;
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::removeSpring( Spring* a )
    {
        springs.erase( std::find(springs.begin(), springs.end(), a) );
        delete a;
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::removeCustomForce( Force* f )
    {
        customForces.erase( std::find(customForces.begin(), customForces.end(), f) );
        delete f;
    }

} } // namespace traer::physics