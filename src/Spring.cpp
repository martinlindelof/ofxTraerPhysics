/*
 * May 29, 2005
 */

// #include <cmath>
#include "Spring.h"

namespace traer { namespace physics {

    /**
    * @author jeffrey traer bernstein
    *
    */

    //--------------------------------------------------------------
    Spring::Spring( Particle* A, Particle* B, const float &ks, const float &d, const float &r )
    {
        springConstant = ks;
        damping = d;
        restLength = r;
        a = A;
        b = B;
        on = true;
    }

    //--------------------------------------------------------------
    Spring::~Spring(){
        
    }
    
    //--------------------------------------------------------------
    void Spring::turnOff()
    {
        on = false;
    }
    
    //--------------------------------------------------------------
    void Spring::turnOn()
    {
        on = true;
    }

    //--------------------------------------------------------------
    bool Spring::isOn() const
    {
        return on;
    }
    
    //--------------------------------------------------------------
    bool Spring::isOff() const
    {
        return !on;
    }
    
    //--------------------------------------------------------------
    Particle* Spring::getOneEnd() const
    {
        return a;
    }
    
    //--------------------------------------------------------------
    Particle* Spring::getTheOtherEnd() const
    {
        return b;
    }
    
    //--------------------------------------------------------------
    float Spring::currentLength() const
    {
        return a->position.distance( b->position );
    }
    
    //--------------------------------------------------------------
    float Spring::getRestLength() const
    {
        return restLength;
    }
    
    //--------------------------------------------------------------
    float Spring::getStrength() const
    {
        return springConstant;
    }
    
    //--------------------------------------------------------------
    void Spring::setStrength( const float &ks )
    {
        springConstant = ks;
    }
    
    //--------------------------------------------------------------
    float Spring::getDamping() const
    {
        return damping;
    }
    
    //--------------------------------------------------------------
    void Spring::setDamping( const float &d )
    {
        damping = d;
    }
    
    //--------------------------------------------------------------
    void Spring::setRestLength( const float &l )
    {
        restLength = l;
    }
    
    //--------------------------------------------------------------
    void Spring::apply()
    {	
        if ( on && ( !a->fixed || !b->fixed ) )
        {
            // ci::Vec3f a2b = a->position - b->position;
            ofVec3f a2b = a->position - b->position;
            
            float a2bDistance = a2b.length();

            // a2b.safeNormalize();            
            a2b.normalize();
        
            // spring force is proportional to how much it stretched 
            
            float springForce = -( a2bDistance - restLength ) * springConstant; 
            
            
            // want velocity along line b/w a & b, damping force is proportional to this
            
            // ci::Vec3f Va2b = a->velocity - b->velocity;
            ofVec3f Va2b = a->velocity - b->velocity;
                                
            float dampingForce = -damping * ( a2b.x*Va2b.x + a2b.y*Va2b.y + a2b.z*Va2b.z );
            
            
            // forceB is same as forceA in opposite direction
            
            float r = springForce + dampingForce;
            
            a2b *= r;
            
            if ( !a->fixed )
                a->force += a2b;
            if ( !b->fixed )
                b->force -= a2b;
        }
    }
    
    //--------------------------------------------------------------
    void Spring::setA( Particle* p )
    {
        a = p;
    }
    
    //--------------------------------------------------------------
    void Spring::setB( Particle* p )
    {
        b = p;
    }

} } // namespace traer::physics