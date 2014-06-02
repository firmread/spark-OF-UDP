#include "ofApp.h"


void ofApp::readXMLdata(){
    ofxXmlSettings settings;
    settings.load("settings.xml");
    ipAddress   = settings.getValue("ipAddress", "");
    port        = settings.getValue("port", 0);
}

//--------------------------------------------------------------
void ofApp::setup(){

    readXMLdata();
    sender.setup(ipAddress, port);
    colors.assign(50, ofColor::pink);

}

//--------------------------------------------------------------
void ofApp::update(){

    
//    if (ofGetMousePressed()){
//        for (int i = 0; i < 50; i++){
//            if (ofRandom(0,1) > 0.9){
//                colors[i] = ofColor(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255));
//            }
//        }
//    }
    
    ofxOscMessage m;
    m.setAddress("/color");

    for (int i = 0; i < 50; i++){
        
        
        int colorAsInt = colors[i].r << 24 | colors[i].g << 16 | colors[i].b << 8;
        
        m.addIntArg(colorAsInt);
        
//        // this is really inefficient !!! :( 
//        m.addIntArg( colors[i].r );
//        m.addIntArg( colors[i].g );
//        m.addIntArg( colors[i].b );
        
    }
    sender.sendMessage(m);
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    
    
    // ------- show which IP address we are sending to
    ofDrawBitmapStringHighlight("sending to " + ipAddress + " on port " + ofToString(port), ofPoint(20,20));

    
    
    // this is where you draw:

    ofFill();
    ofSetColor(255,0,0);
    ofRect(mouseX, mouseY,20,500);

    // grab the drawing and put it into the color array
    
    centerOfScreen.grabScreen(0,175, ofGetWidth(), 50);
    centerOfScreen.resize(50,1);
   
    for (int i = 0; i < 50; i++){
        ofColor color = centerOfScreen.getColor(i, 0);
        colors[i] = color;
    }
    
    
    ofSetColor(ofColor::white);
    ofNoFill();
    ofRect( 0, 200 -25, ofGetWidth(), 50);
    
    
    
    // ------- draw colors at the base of the window
    float width = ofGetWidth() / (float)colors.size();
    for (int i = 0; i < colors.size(); i++){
        
        
        ofSetColor(colors[i]);
        ofFill();
        ofRect(i*width, ofGetHeight(), width-1, -30);
        
        if (colors[i].getBrightness() < 10){
            // white outline
            ofSetColor(ofColor::white);
            ofNoFill();
            ofRect(i*width, ofGetHeight(), width-1, -30);
        } else {
            // black outline
            ofSetColor(ofColor::black);
            ofNoFill();
            ofRect(i*width, ofGetHeight(), width-1, -30);
        }
        
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
