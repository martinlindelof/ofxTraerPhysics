/*

88                                         88
88                                         88
88                                         88
88,dPPYba,   ,adPPYba, ,adPPYYba,  ,adPPYb,88  ,adPPYba, 8b,dPPYba,
88P'    "8a a8P_____88 ""     `Y8 a8"    `Y88 a8P_____88 88P'   "Y8
88       88 8PP""""""" ,adPPPPP88 8b       88 8PP""""""" 88
88       88 "8b,   ,aa 88,    ,88 "8a,   ,d88 "8b,   ,aa 88
88       88  `"Ybbd8"' `"8bbdP"Y8  `"8bbdP"Y8  `"Ybbd8"' 88


  		@author Martin Lindelof
  		@description
*/

#pragma once

#include "ofMain.h"
#include "ofxTraerPhysics.h"

using namespace traer::physics;

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ParticleSystem* 	s;
		Particle* 			p_mouse;
		vector< vector< Particle* > > p_fixed;
		vector< vector< Particle* > > p_free;
};
