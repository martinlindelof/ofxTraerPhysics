/*

  ,ad8888ba,
 d8"'    `"8b   aa         aa
d8'             88         88
88          aaaa88aaaa aaaa88aaaa
88          """"88"""" """"88""""
Y8,             88         88
 Y8a.    .a8P   ""         ""
  `"Y8888Y"'


  		@author Martin Lindelof
  		@description ofxTraerPhysics grid example app
  		traer physics creator, http://murderandcreate.com/physics/
  		openframeworks.cc
  		libcinder.org

*/

#include "testApp.h"

#define PHYS_GRAVITY 		0.0
#define PHYS_DRAG 			0.2
#define SPRING_STRENGTH 	0.03
#define SPRING_DAMPING 		0.01
#define MOUSE_STRENGTH 		96000
#define MOUSE_SLOPE 		180

#define GRID_START_X		180
#define GRID_START_Y 		130
#define GRID_SPACE_X		130
#define GRID_SPACE_Y 		100


//--------------------------------------------------------------
void testApp::setup(){

	ofSetVerticalSync( true );
	ofSetWindowTitle("Traer Physics Spring Particles");

	s = new ParticleSystem(PHYS_GRAVITY, PHYS_DRAG);
	s->clear();

	p_mouse = s->makeParticle(1.0, 0.0, 0.0, 0.0);
	p_mouse->setFixed( true );

	for (int x = 0; x < 6; ++x)
	{
		vector< Particle* > p_cols_fixed;
		vector< Particle* > p_cols_free;

		for (int y = 0; y < 6; ++y)
		{
			// grid
			Particle* _p_fixed = s->makeParticle(0.5, GRID_START_X+x*GRID_SPACE_X, GRID_START_Y+y*GRID_SPACE_Y, 0);
			Particle* _p_free = s->makeParticle(0.5, GRID_START_X+x*GRID_SPACE_X, GRID_START_Y+y*GRID_SPACE_Y, 0);
			_p_fixed->setFixed( true );

			s->makeSpring(_p_fixed, _p_free, SPRING_STRENGTH, SPRING_DAMPING, 0.0);
			s->makeAttraction(p_mouse, _p_free, MOUSE_STRENGTH, MOUSE_SLOPE);

			p_cols_fixed.push_back(_p_fixed);
			p_cols_free.push_back(_p_free);

		}

		p_fixed.push_back(p_cols_fixed);
		p_free.push_back(p_cols_free);

	}

}

//--------------------------------------------------------------
void testApp::update(){

	p_mouse->position.set(mouseX, mouseY, 0);
	s->tick();

}

//--------------------------------------------------------------
void testApp::draw(){

	ofBackground(100);
	ofNoFill();
	ofSetColor(200,200,125);
	ofSetCircleResolution(60);
	ofCircle(p_mouse->position, MOUSE_SLOPE);

	ofFill();

	for (int x = 0; x < 6; ++x){
		for (int y = 0; y < 6; ++y){
			ofSetColor(80);
			ofSetCircleResolution(20);
			ofCircle(p_fixed[x][y]->position, 10);

			ofSetColor(125,220,250);
			ofLine(p_fixed[x][y]->position, p_free[x][y]->position);

			ofSetColor(125,200,180);
			ofCircle(p_free[x][y]->position, 9);
		}
	}

	ofDrawBitmapStringHighlight("ofxTraerPhysics, Grid example", 0, 20);
	ofDrawBitmapStringHighlight("www.openframworks.cc", 0, 40);
	ofDrawBitmapStringHighlight("p_mouse : "+ofToString(p_mouse->position)+" R"+ofToString(MOUSE_SLOPE), 0, 60);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}