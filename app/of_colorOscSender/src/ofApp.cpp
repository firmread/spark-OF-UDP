#include "ofApp.h"
#include "baseScene.h"
#include "messagesScene.h"
#include "pulseScene.h"


int whichScene = 0;
//--------------------------------------------------------------
void ofApp::setup(){

    sender.setup();

    img.loadImage("band.png");
    pos = -img.getWidth();
    

    scenes.push_back(new messagesScene());
    scenes.push_back(new pulseScene());
    scenes.push_back(new crazyScene());
    scenes.push_back(new movieScene());
    scenes.push_back(new patternScene());
    scenes.push_back(new recordedPulseScene());
    
    for (int i = 0; i < scenes.size(); i++){
        scenes[i]->setup();
    }
    
    
    blur.setup(ofGetWidth(), ofGetHeight());
}


//--------------------------------------------------------------
void ofApp::update(){

    sender.send();
    
    scenes[whichScene]->update();
    
  
}


//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);
    scenes[whichScene]->draw();
    
    sender.grabScreen();
    
    sender.drawWherePickingFrom();
    sender.drawSentColors();
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    
    if (key == ' '){
        whichScene ++;
        whichScene %= scenes.size();
    }
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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
