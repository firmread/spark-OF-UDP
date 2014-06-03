#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup(){

    sender.setup();

    img.loadImage("band.png");
    pos = -img.getWidth();
}


//--------------------------------------------------------------
void ofApp::update(){

    sender.send();
    
    pos += 1.0;
    if (pos > 120){
        pos = -img.getWidth();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    if (ofGetFrameNum() % 3 == 0){
        ofClear(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255));
    } else {
        ofClear(0,0,0);
        
    }
    ofFill();
    ofSetColor(255,255,255);
    img.draw(pos, 0); //(mouseX,0,500,500);
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
