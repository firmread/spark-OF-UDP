#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetCircleResolution(100);
    
	udp.Create();
	udp.Bind(7777);
    udp.SetNonBlocking(true);
    heart.setup(500);
}



//--------------------------------------------------------------
void ofApp::update(){
    
    
    
	char udpMessage[sizeof(sparkyToOFPacket)];
    memset(udpMessage, 0, sizeof(sparkyToOFPacket));
    int nBytesRevd = udp.Receive(udpMessage, sizeof(sparkyToOFPacket));
    
    
	if(nBytesRevd == sizeof(sparkyToOFPacket)){
        bGotSth = true;
        
        cout << "got data" << endl;
        //get info to packet
        memset(&S2Opacket, 0, sizeof(sparkyToOFPacket));
        memcpy(&S2Opacket, udpMessage, sizeof(sparkyToOFPacket));
        
        
        packetHandler ph(S2Opacket);
//        //time
//        cout << S2Opacket.millisRunning << endl;
//        
//        //ip
//        int ip[4];
//        ip[0] = S2Opacket.ipSpark >> 24 & 0xFF;
//        ip[1] = S2Opacket.ipSpark >> 16 & 0xFF;
//        ip[2] = S2Opacket.ipSpark >> 8 & 0xFF;
//        ip[3] = S2Opacket.ipSpark & 0xFF;
//        cout << ip[0] << "." << ip[1]<< "." << ip[2]<< "."<< ip[3]<< endl;
//        string tempIp = ofToString(ip[0]) + "." + ofToString(ip[1]) + "."
//        + ofToString(ip[2]) + "." + ofToString(ip[3]);
//        
//        //uuid
//        string uuid( S2Opacket.uuid, S2Opacket.uuid + sizeof S2Opacket.uuid / sizeof S2Opacket.uuid[0] );
//        cout << uuid << endl;
        
        bool bDoesThisSparkExist = false;
        for (int i = 0; i < sparks.size(); i++){
            if (sparks[i].ip == ph.ipSparkString){
                cout << "ph.ipSparkString : " << i << " : " << sparks[i].ip << endl;
                bDoesThisSparkExist = true;
            }
        }
        
        // register it if we never seen it before
        if (!bDoesThisSparkExist){
            spark temp;
            //temp.setup(S2Opacket);
            
            /*
            
             << this is not working!!!
            vector is passing by copy
            udp is a complicate things << therefore copy won't work
            it could works in this sequence only if it's a vector of pointer
             
             */
            
            cout << "create object for " << ph.ipSparkString << endl;
            
            sparks.push_back(temp);
            sparks[sparks.size()-1].setup(S2Opacket);
            
        // otherwise, welcome back our beloved sparky!  !
        } else {
            
            for (int i = 0; i< sparks.size(); i++) {
                if(sparks[i].ip == ph.ipSparkString){
                    sparks[i].readPacketFromSpark(S2Opacket);
                }
            }
        }

    } else {
        
        bGotSth = false;
    }
    
    for (int i =0; i< sparks.size(); i++){
        sparks[i].update();
//        cout << "updating" << i << endl;
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofBackgroundGradient(80, 0);
    string sparksNo = ofToString(sparks.size());

    for (int i =0; i< sparks.size(); i++){
        sparks[i].draw(100, 100+100*i);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
    if (key == ' '){
        fireDiscovery();
    }
    
}

//--------------------------------------------------------------
void ofApp::fireDiscovery(){
    
    // let's do discovery:
    
    memset(&O2Spacket, 0, sizeof(ofToSparkyPacket));
    O2Spacket.packetType = PACKET_TYPE_DISCOVERY;
    O2Spacket.ofPacketSentOutTime = ofGetElapsedTimef();
    getOfLocalIp readIp;
    O2Spacket.ofIp = readIp.getInt();
    char packetBytes[sizeof(ofToSparkyPacket)];
    memcpy(packetBytes, &O2Spacket, sizeof(ofToSparkyPacket));
    
    ofxUDPManager udp4discovery;
    
    for (int i = 0; i < 256; i++){
        
        string IP = "192.168.2." + ofToString(i);
        
        bool bFoundAlready = false;
        for (int j = 0; j < sparks.size(); j++){
            if (sparks[j].ip == IP){
                bFoundAlready = true;
            }
        }
        
        if (!bFoundAlready){
            udp4discovery.Create();
            udp4discovery.Connect(IP.c_str(),8888);
            udp4discovery.SetNonBlocking(false);
            udp4discovery.Send(packetBytes,sizeof(ofToSparkyPacket));
            //ofSleepMillis(30);
        }
    }
    

}




//
//string ofApp::convertIpToString(int ip){
//    
//    
//    int temp[4];
//    temp[0] = ip >> 24 & 0xFF;
//    temp[1] = ip >> 16 & 0xFF;
//    temp[2] = ip >> 8 & 0xFF;
//    temp[3] = ip & 0xFF;
//    cout << temp[0] << "." << temp[1]<< "." << temp[2]<< "."<< temp[3]<< endl;
//    
//    
//    string tempIp = ofToString(temp[0]) + "." + ofToString(temp[1]) + "."
//    + ofToString(temp[2]) + "." + ofToString(temp[3]);
//
//    return tempIp;
//}

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
