#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup(){

    sender.setup();
}

//--------------------------------------------------------------
void ofApp::update(){

    sender.send();
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofClear(255,255,255);
    ofFill();
    ofSetColor(255,0,0);
    ofRect(mouseX,0,500,500);
    
    ofDisableAlphaBlending();
    sender.grabScreen();
    

    
    sender.drawSentColors();

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
