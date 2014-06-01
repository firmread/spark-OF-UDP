#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetCircleResolution(100);
    
	udp.Create();
	udp.Bind(7777);
    udp.SetNonBlocking(true);
    //heart.setup(500);
}



//--------------------------------------------------------------
void ofApp::update(){
    
    
    if (ofGetMousePressed()){
        fireControl();
        
    }
    
	char udpMessage[sizeof(sparkyToOFPacket)];
    memset(udpMessage, 0, sizeof(sparkyToOFPacket));
    
    
    bool bAnyAvailable = true;
    
    while (bAnyAvailable == true){
        int nBytesRevd = udp.Receive(udpMessage, sizeof(sparkyToOFPacket));
        
        if (nBytesRevd <= 0) bAnyAvailable = false;
        
        
        if(nBytesRevd == sizeof(sparkyToOFPacket)){
            bGotSth = true;
            
            cout << "got data" << endl;
            //get info to packet
            memset(&S2Opacket, 0, sizeof(sparkyToOFPacket));
            memcpy(&S2Opacket, udpMessage, sizeof(sparkyToOFPacket));
            
            
            packetHandler ph(S2Opacket);
            
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

        }
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
    
    if (key == 'c'){
        fireControl();
        
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
        
        string IP = "192.168.1." + ofToString(i);
        
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
//--------------------------------------------------------------
void ofApp::fireControl(){
    
    // let's do discovery:
    
    memset(&O2Spacket, 0, sizeof(ofToSparkyPacket));
    O2Spacket.packetType = PACKET_TYPE_COLOR;
    O2Spacket.ofPacketSentOutTime = ofGetElapsedTimef();
    getOfLocalIp readIp;
    O2Spacket.ofIp = readIp.getInt();
    O2Spacket.r =  sin(ofGetElapsedTimef()) *50 + 50;
    O2Spacket.g =  sin(ofGetElapsedTimef() + PI/3) * 50 + 50;
    O2Spacket.b =  sin(ofGetElapsedTimef() + 2*PI/3) * 50 + 50;
    
    char packetBytes[sizeof(ofToSparkyPacket)];
    memcpy(packetBytes, &O2Spacket, sizeof(ofToSparkyPacket));
    
    for (int i=0; i<sparks.size(); i++) {
        
        
        sparks[i].udp.Create();
        sparks[i].udp.Connect(sparks[i].ip.c_str(), 8888);
        int sent = sparks[i].udp.Send(packetBytes, sizeof(ofToSparkyPacket));
        cout << sent << " " << sparks[i].ip << endl;
        sparks[i].udp.Close();

        
        
        //sparks[i].udp.Send(packetBytes, sizeof(ofToSparkyPacket));
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
    //fireControl();
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
