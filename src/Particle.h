#pragma once

// #include "cinder/Vector.h"
#include "ofMain.h"

namespace traer { namespace physics {

class Particle
{
    public:  
      
        Particle();
        Particle( const float &m );
        ~Particle();
    	void setLocked( bool b ){ locked = b; };
    	void setFixed( bool b ){ if( !locked ) fixed = b; };
        void makeFixed();
        // ci::Vec3f position;
        // ci::Vec3f velocity;
        // ci::Vec3f force;
        ofVec3f position;
        ofVec3f velocity;
        ofVec3f force;
        float mass;
        float age;
        bool fixed;
    	bool locked;
        
        void reset();
  
};

} } // namespace traer::physics