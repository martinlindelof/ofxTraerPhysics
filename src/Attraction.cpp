// attract positive repel negative

// #include <cmath>
// #include "cinder/Vector.h"
#include "Attraction.h"

namespace traer { namespace physics {
	
    Attraction::Attraction( Particle* _a, Particle* _b, float _k, float _distanceMin )
	{
		a = _a;
		b = _b;
		k = _k;
		on = true;
		distanceMin = _distanceMin;
		distanceMinSquared = distanceMin*distanceMin;
	}

	float Attraction::getMinimumDistance()
	{
		return distanceMin;
	}

	void Attraction::setMinimumDistance( float d )
	{
		distanceMin = d;
		distanceMinSquared = d*d;
	}

	void Attraction::turnOff()
	{
		on = false;
	}

	void Attraction::turnOn()
	{
		on = true;
	}

	void Attraction::setStrength( float _k )
	{
		k = k;
	}

	Particle* Attraction::getOneEnd()
	{
		return a;
	}

	Particle* Attraction::getTheOtherEnd()
	{
		return b;
	}

	void Attraction::apply()
	{
		if ( on && ( !a->fixed || !b->fixed ) )
		{
            // ci::Vec3f a2b = a->position - b->position;
            ofVec3f a2b = a->position - b->position;

			float a2bX = a->position.x - b->position.x;
			float a2bY = a->position.y - b->position.y;
			float a2bZ = a->position.z - b->position.z;
			
			
			float a2bDistanceSquared = a2bX*a2bX + a2bY*a2bY + a2bZ*a2bZ;
			
			if ( a2bDistanceSquared < distanceMinSquared )
			    a2bDistanceSquared = distanceMinSquared;
			
			float force = k * a->mass * b->mass / a2bDistanceSquared;
			
			float length = (float)sqrt( a2bDistanceSquared );
			
			// make unit vector
			
			a2bX /= length;
			a2bY /= length;
			a2bZ /= length;
			
			// multiply by force
			
			a2bX *= force;
			a2bY *= force;
			a2bZ *= force;
			
			// apply
			
			if ( !a->fixed )a->force += ofVec3f( -a2bX, -a2bY, -a2bZ );
			if ( !b->fixed )b->force += ofVec3f( a2bX, a2bY, a2bZ );
		}
	}

	float Attraction::getStrength()
	{
		return k;
	}

	bool Attraction::isOn() const
	{
		return on;
	}

	bool Attraction::isOff() const
	{
		return !on;
	}

    float Attraction::Q_rsqrt( float number )
    {
        long i;
        float x2, y;
        const float threehalfs = 1.5F;
        
        x2 = number * 0.5F;
        y  = number;
        i  = * ( long * ) &y;                       // evil floating point bit level hacking [sic]
        i  = 0x5f3759df - ( i >> 1 );               // what the fuck? [sic]
        y  = * ( float * ) &i;
        y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
        //    y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
        
        return y;
    }

} } // namespace traer::physics
