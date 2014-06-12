//
//  particleScene.cpp
//  of_colorOscSender
//
//  Created by Firm Read on 6/11/14.
//
//


#include "particleScene.h"



//--------------------------------------------------------------
void particleScene::setup(){
    particles.clear();
	for (int i = 0; i < 100; i++){
		particle myParticle;
        float r = ofRandom(-4,4);
        float angle = ofRandom(180);
		float vx = r*cos(angle);
		float vy = r*sin(angle);
		myParticle.setInitialCondition(300,300,vx, vy);
		// more interesting with diversity :)
		// uncomment this:
		myParticle.damping = ofRandom(0.01, 0.05);
		particles.push_back(myParticle);
	}
	
}

//--------------------------------------------------------------
void particleScene::update(){
    
	// on every frame
	// we reset the forces
	// add in any forces on the particle
	// perfom damping and
	// then update
	
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].resetForce();
//		particles[i].addForce(0,0.04);  // gravity
//		particles[i].addDampingForce();
		particles[i].update();
        particles[i].bounceOffWalls();
	}
    
}

//--------------------------------------------------------------
void particleScene::draw(){
    
	ofSetColor(255,100);
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].draw();
	}
    
    ofDrawBitmapStringHighlight("particle scene", 20, 60);
    
}


//--------------------------------------------------------------
void particleScene::mousePressed(int x, int y, int button){
	for (int i = 0; i < particles.size(); i++){
        float r = ofRandom(-4,4);
        float angle = ofRandom(180);
		float vx = r*cos(angle);
		float vy = r*sin(angle);
		particles[i].setInitialCondition(x,y,vx, vy);
    
	}
}


void particleScene::mouseDragged(int x , int y , int button){
    
}