#include "testApp.h"
#include "communicationTypes.h"



//--------------------------------------------------------------
void testApp::setup(){

    
//    cout << sizeof(float) << endl;
//    cout << sizeof(int) << endl;
//    cout << sizeof(packet) << endl;
    
    
    //----------------------------------
 
    
    
    
    
    
    
}

//--------------------------------------------------------------
void testApp::update(){

    // copy struct to bytes:
    
    packet p;
    p.time = ofGetElapsedTimef();
    p.frameNumber = ofGetFrameNum();
    p.random = ofRandom(0,1);
    char packetBytes[sizeof(packet)];
    memcpy(packetBytes, &p, sizeof(packet));
    
    // go from bytes to packet:
    
    packet newPacket;
    memcpy(&newPacket, packetBytes, sizeof(packet));
    cout << p.frameNumber << " " << newPacket.frameNumber << endl;
}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
