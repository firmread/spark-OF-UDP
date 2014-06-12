#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup(){

    sender.setup();

//    img.loadImage("band.png");
//    pos = -img.getWidth();
    
    
    
    scenes.push_back( new animation01());
    
    for (int i = 0 ; i<scenes.size(); i++) {
        scenes[i]->setup();
    }
    
    //blur
    blur.setup(ofGetWidth(), ofGetHeight(), 4, .2, 4);
    blurness = 0;
    
    
}


//--------------------------------------------------------------
void ofApp::update(){

    sender.send();
    
//    pos += 1.0;
//    if (pos > 120){
//        pos = -img.getWidth();
//    }
    
    
    
    scenes[currentScene]->update();
    
    
    //blur
    blur.setScale(blurness);
//                  ofMap(mouseX, 0, ofGetWidth(), 0, 1));
    blur.setRotation(ofMap(mouseY, 0, ofGetHeight(), -PI, PI));
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){

//    if (ofGetFrameNum() % 3 == 0){
//        ofClear(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255));
//    } else {
//        ofClear(0,0,0);
//        
//    }
    
    
    blur.begin();
    ofPushStyle();
    scenes[currentScene]->draw();
    ofPopStyle();
    blur.end();
    
    blur.draw();
    
    sender.grabScreen();
    sender.drawSentColors();
    
    ofDrawBitmapString("blur : " + ofToString(blurness), 20,20);
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    blurness +=.1;
    if (blurness > 1) blurness = 0;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    scenes[currentScene]->mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    scenes[currentScene]->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    scenes[currentScene]->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    
    scenes[currentScene]->mouseReleased(x, y, button);
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
