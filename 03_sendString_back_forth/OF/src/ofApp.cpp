#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
	udpSend.Create();
	udpSend.Connect("192.168.2.48",8888);
	udpSend.SetNonBlocking(true);
    
    udpRece.Create();
    udpRece.Bind(7777);
    udpRece.SetNonBlocking(true);
}

//--------------------------------------------------------------
void ofApp::update(){
    
	char udpMessage[50];
//	cout << udpRece.Receive(udpMessage,50) << endl;
    memset(udpMessage, 0, 50);
    udpRece.Receive(udpMessage,50);
    
//    udpRece
	string message = udpMessage;
	if(message!=""){
        cout << message << endl;
        bGotSth = true;
        
        bitmapstring = message;
    }
    else bGotSth = false;
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (bGotSth) {
        ofBackground(ofColor::red);
    }
    else ofBackground(127);
    ofDrawBitmapStringHighlight(bitmapstring, 100,100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    string something = "abcd";
    udpSend.Send(something.c_str(),something.length());
    
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
