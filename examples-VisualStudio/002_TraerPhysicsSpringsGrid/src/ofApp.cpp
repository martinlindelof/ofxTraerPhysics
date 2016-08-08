#include "ofApp.h"

#define PHYS_GRAVITY 		0.0
#define PHYS_DRAG 			0.4
#define SPRING_STRENGTH 	0.24
#define SPRING_DAMPING 		0.01
#define MOUSE_STRENGTH 		-60000
#define MOUSE_SLOPE 		140

#define GRID_START_X		180
#define GRID_START_Y 		130
#define GRID_SPACE_X		130
#define GRID_SPACE_Y 		100

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetWindowTitle("Traer Physics Springs Grid");

	s = new ParticleSystem(PHYS_GRAVITY, PHYS_DRAG);
	s->clear();

	p_mouse = s->makeParticle(10, 0.0, 0.0, 0.0);
	p_mouse->setFixed(true);

	for (int x = 0; x < 6; ++x)
	{
		// grid cols
		vector< Particle* > p_cols_fixed;
		vector< Particle* > p_cols_free;

		for (int y = 0; y < 6; ++y)
		{
			// grid rows
			Particle* _p_fixed = s->makeParticle(0.5, GRID_START_X + x*GRID_SPACE_X, GRID_START_Y + y*GRID_SPACE_Y, 0);
			Particle* _p_free = s->makeParticle(0.5, GRID_START_X + x*GRID_SPACE_X, GRID_START_Y + y*GRID_SPACE_Y, 0);
			_p_fixed->setFixed(true);

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
void ofApp::update(){
	p_mouse->position.set(mouseX, mouseY, 0);
	s->tick();
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofBackground(120);


	// lets draw the particle mouse position
	ofSetColor(250, 220, 120, 50);

	ofSetCircleResolution(30);
	ofDrawCircle(mouseX, mouseY, MOUSE_SLOPE);
	

	ofSetCircleResolution(12);

	// lets draw the grid
	for (int x = 0; x < 6; x++)
	{
		for (int y = 0; y < 6; y++)
		{
			ofSetColor(80);
			ofDrawCircle(p_fixed[x][y]->position, 10);

			ofSetColor(60);
			ofDrawLine(p_fixed[x][y]->position, p_free[x][y]->position);

			ofSetColor(220, 120, 240);
			ofDrawCircle(p_free[x][y]->position, 9);
		}
	}

	
	ofDrawBitmapStringHighlight("Traer Physics : Springs Grid", 0, 20);
	ofDrawBitmapStringHighlight("www.openframeworks.cc", 0, 40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	s->setGravity(10);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	s->setGravity(0);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
