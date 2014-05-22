#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
	udp.Create();
	udp.Connect("192.168.2.48",8888);
    udp.Bind(7777);
    udp.SetNonBlocking(true);
    
    delay = 500;
    t.setup(100);
}

//--------------------------------------------------------------
void ofApp::update(){
    
	char udpMessage[50];
    memset(udpMessage, 0, 50);
    udp.Receive(udpMessage,50);
    
//    udp
	string message = udpMessage;
	if(message!=""){
        cout << message << endl;
        bGotSth = true;
        
        bitmapstring = message;
    }
    else bGotSth = false;
    
    
    
    
    //trigger
    t.update(ofGetElapsedTimeMillis());
    if (t.bTimerFired()){
        
        p.frameNumber = ofGetFrameNum();
        p.time = ofGetElapsedTimef();
        char packetBytes[sizeof(packet)];
        memcpy(packetBytes, &p, sizeof(packet));
        
        udp.Send(packetBytes,sizeof(packet));

    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (bGotSth) {
        ofBackground(ofColor::red);
    }
    else ofBackground(200);
    
    ofDrawBitmapStringHighlight(bitmapstring, 100,100);
    ofDrawBitmapStringHighlight(ofToString(ofMap(mouseX, 0, ofGetWidth(), 100, 1000)), mouseX, mouseY);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
//    string something = "abcd";
    

    p.frameNumber = ofGetFrameNum();
    p.time = ofGetElapsedTimef();
    char packetBytes[sizeof(packet)];
    memcpy(packetBytes, &p, sizeof(packet));

    udp.Send(packetBytes,sizeof(packet));
    
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
    delay = ofMap(x, 0, ofGetWidth(), 100, 1000, true);
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
