#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    
	udp.Create();
	udp.Connect("192.168.2.17",8888);
    udp.Bind(7777);
    udp.SetNonBlocking(true);
    
    delay = 500;
    t.setup(100);
    line1 = line2 = line3 = "";
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
	char udpMessage[sizeof(sparkyToOFPacket)];
    memset(udpMessage, 0, sizeof(sparkyToOFPacket));
    int nBytesRevd = udp.Receive(udpMessage, sizeof(sparkyToOFPacket));
    
    
	if(nBytesRevd == sizeof(sparkyToOFPacket)){
        bGotSth = true;
        
        memset(&rp, 0, sizeof(sparkyToOFPacket));
        memcpy(&rp, udpMessage, sizeof(sparkyToOFPacket));
        
        //time
        cout << rp.millisRunning << endl;
        
        //ip
        ip[0] = rp.ip >> 24 & 0xFF;
        ip[1] = rp.ip >> 16 & 0xFF;
        ip[2] = rp.ip >> 8 & 0xFF;
        ip[3] = rp.ip & 0xFF;
        cout << ip[0] << "." << ip[1]<< "." << ip[2]<< "."<< ip[3]<< endl;
        
        //uuid
        
        string temp( rp.uuid, rp.uuid + sizeof rp.uuid / sizeof rp.uuid[0] );
        uuid = temp;
        cout << uuid << endl;
        
        
        line1 = "time spark been running (ms) = " + ofToString(rp.millisRunning);
        line2 = "ip = " + ofToString(ip[0]) + "." + ofToString(ip[1]) + "."
                        + ofToString(ip[2]) + "." + ofToString(ip[3]);
        line3 = "uuid = " + ofToString(uuid);
        
        
    }
    else {
    
        bGotSth = false;
    }
    
    
    
    // time trigger
    // packing packet to spark
    t.update(ofGetElapsedTimeMillis());
    if (t.bTimerFired()){
        p.time = ofGetElapsedTimef();
        p.r = mouseX;
        p.g = mouseY;
        p.b = mouseX + mouseY;
        
        char packetBytes[sizeof(ofToSparkyPacket)];
        memcpy(packetBytes, &p, sizeof(ofToSparkyPacket));
        udp.Send(packetBytes,sizeof(ofToSparkyPacket));

    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (bGotSth) {
        ofBackground(255,0,0);
    }
    else ofBackground(200);
    
    ofDrawBitmapStringHighlight(line1 + "\n" + line2 + "\n" + line3, 100,100);
    ofDrawBitmapStringHighlight(ofToString(ofMap(mouseX, 0, ofGetWidth(), 100, 1000)), mouseX, mouseY);
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
