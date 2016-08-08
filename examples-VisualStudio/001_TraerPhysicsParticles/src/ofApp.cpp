#include "ofApp.h"

#define PHYS_GRAVITY		0.0
#define PHYS_DRAG			0.2
#define MOUSE_STRENGTH		96000
#define MOUSE_SLOPE			180



//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(true);
	ofSetWindowTitle("Traer Physics Particles");

	s = new ParticleSystem(PHYS_GRAVITY, PHYS_DRAG);
	s->clear();

	p_mouse = s->makeParticle(1.0, 0.0, 0.0, 0.0);
	p_mouse->setFixed(true);

	// create all the particles
	for (int i = 0; i < 500; i++)
	{
		Particle* _p = s->makeParticle(0.5, ofRandom(1024), ofRandom(640), 0);
		s->makeAttraction(p_mouse, _p, MOUSE_STRENGTH, MOUSE_SLOPE);

		particles.push_back(_p);
	}

}

//--------------------------------------------------------------
void ofApp::update(){

	p_mouse->position.set(mouseX, mouseY, 0);
	s->tick();

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofBackground(120);
	ofDrawBitmapStringHighlight("Traer Physics :: Particles Example Visual Studio", 0, 20);
	ofDrawBitmapStringHighlight("www.openframeworks.cc", 0, 40);

	ofSetColor(230, 230, 150);
	ofSetCircleResolution(30);
	ofDrawCircle(p_mouse->position, MOUSE_SLOPE*0.25);

	ofSetColor(120, 250, 140);
	ofSetCircleResolution(12);
	
	for (int i = 0; i < particles.size(); i++)
	{
		ofDrawCircle(particles[i]->position, 10);
	}

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
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i]->position.set(ofRandom(1024), ofRandom(640), 0);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
