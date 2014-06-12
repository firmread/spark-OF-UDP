
//
//  noiseScene.cpp
//  of_colorOscSender
//
//  Created by Firm Read on 6/11/14.
//
//

#include "ballScene.h"


void ballScene::setup(){
    
    for (int i = 0 ; i< 1000; i++) {
        simpleParticle temp;
        temp.setup();
        temp.x = ofRandom(ofGetWidth());
        temp.y = ofRandom(ofGetHeight());
        temp.xspeed = ofRandom(0.50);
        temp.yspeed = ofRandom(0.50);
//        temp.c.set(255);
        temp.c.setHsb(ofRandom(255), 255, 255);
        sp.push_back(temp);
        
        sineAlphaSpeed = 0.005;
        minAlpha = 20;
    }
}



void ballScene::update(){
 
    for (int i = 0 ; i<sp.size(); i++) {
        sp[i].update();
        sp[i].jumpsToTheOtherSide();
        
        float sine = sin(ofGetElapsedTimef() * i * sineAlphaSpeed + i);
        minAlpha = ofMap(mousePos.x , 0,  ofGetWidth(), 0, 255);
        sine = ofMap(sine, -1, 1, minAlpha, 255);
        sp[i].setAlpha(sine);
    }
}


void ballScene::draw(){
    
    for (int i = 0; i< sp.size(); i++) {
        sp[i].draw();
    }
    
    ofDrawBitmapStringHighlight("ball scene", 20, 60);
}


void ballScene::mouseDragged(int x, int y, int button){
    for (int i = 0 ; i< sp.size(); i++) {
        sp[i].addAttractionForce(x, y, 10000, 1.0);
    }
}

void ballScene::mouseMoved(int x, int y){
    mousePos.set(x,y);
}