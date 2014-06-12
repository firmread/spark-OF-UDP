#include "ofApp.h"


int whichScene = 0;
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    sender.setup();
    ofEnableAlphaBlending();
    
    scenes.push_back(new collidingMessageScene());
    scenes.push_back(new patternScene());
    scenes.push_back(new pulseScene());
    scenes.push_back(new ballScene());
    scenes.push_back(new recordedPulseScene());
    scenes.push_back(new crazyScene());
    scenes.push_back(new particleScene());
    scenes.push_back(new messagesScene());
    scenes.push_back(new movieScene());
    
    for (int i = 0; i < scenes.size(); i++){
        scenes[i]->setup();
    }
    
//    blur.setup(ofGetWidth(), ofGetHeight(), 4, .2, 4);
    
//    blur.setup(ofGetWidth(), ofGetHeight());
//    blurness = 0;
    bHoldingReturn = false;
}


//--------------------------------------------------------------
void ofApp::update(){

    sender.send();
    
    scenes[whichScene]->update();
    
    
    //flash
    if (bFadeAlpha) {
        flashAlpha -= 10;
        if (flashAlpha <= 0) {
            bFadeAlpha = false;
        }
    }
    
//    blur.setScale(0);
//    blur.setScale(blurness);
//    blur.setRotation(ofMap(mouseY, 0, ofGetHeight(), -PI, PI));
}


//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);

    ofPushStyle();
    scenes[whichScene]->draw();
    ofPopStyle();
    
    //flash
    if (bHitReturnFlash) {
        bHitReturnFlash = false;
        bFadeAlpha = true;
        scenes[whichScene]->setup();
    }
    if (flashAlpha > 0 ) {
        ofSetColor(255, flashAlpha);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
    }
    
    //grab to colorsender
    sender.grabScreen();
    
    sender.drawWherePickingFrom();
    sender.drawSentColors();
    
    ofDrawBitmapStringHighlight("scene : " + ofToString(whichScene)
                                + " / " + ofToString(scenes.size()-1)
                                + "\n'space' = next scene, 'return' = flash"
                                ,20,20);
    
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    
    if (key == ' '){
        whichScene ++;
        whichScene %= scenes.size();
    }
    
    //flash
    if (key == OF_KEY_RETURN){
        flashAlpha = 255;
        bHoldingReturn = true;
        bHitReturnFlash = true;
    }
//    if (key == 'a'){
//        scenes[whichScene]->blurness += 0.1;
//        if (scenes[whichScene]->blurness > 2.0)scenes[whichScene]->blurness = 0;
//    }
    
//    if (key == 'z') {
//        
//        blurness +=.1;
//        if (blurness > 1) blurness = 0;
//    }
    scenes[whichScene]->keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    scenes[whichScene]->keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    scenes[whichScene]->mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    scenes[whichScene]->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    scenes[whichScene]->mousePressed(x,y,button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    scenes[whichScene]->mouseReleased(x, y, button);
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
