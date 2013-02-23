#pragma once

// #include <vector>
// #include "cinder/Vector.h"
#include "ofMain.h"
#include "Integrator.h"
#include "ParticleSystem.h"

namespace traer { namespace physics {

class RungeKuttaIntegrator : public Integrator
{

	public:

		// std::vector<ci::Vec3f> originalPositions;
		// std::vector<ci::Vec3f> originalVelocities;
		// std::vector<ci::Vec3f> k1Forces;
		// std::vector<ci::Vec3f> k1Velocities;
		// std::vector<ci::Vec3f> k2Forces;
		// std::vector<ci::Vec3f> k2Velocities;
		// std::vector<ci::Vec3f> k3Forces;
		// std::vector<ci::Vec3f> k3Velocities;
		// std::vector<ci::Vec3f> k4Forces;
		// std::vector<ci::Vec3f> k4Velocities;

		vector<ofVec3f> originalPositions;
		vector<ofVec3f> originalVelocities;
		vector<ofVec3f> k1Forces;
		vector<ofVec3f> k1Velocities;
		vector<ofVec3f> k2Forces;
		vector<ofVec3f> k2Velocities;
		vector<ofVec3f> k3Forces;
		vector<ofVec3f> k3Velocities;
		vector<ofVec3f> k4Forces;
		vector<ofVec3f> k4Velocities;
		
		ParticleSystem* s;
		
		RungeKuttaIntegrator( ParticleSystem* s );
		~RungeKuttaIntegrator();
		
		void allocateParticles();
		
		void step( const float &deltaT );

};

} } // namespace traer::physics