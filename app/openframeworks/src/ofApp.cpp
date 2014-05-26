#include "ofApp.h"


//find out my ip through this cmd!
std::string exec(const char* cmd) {
    
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
        
        if(fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    
    pclose(pipe);
    return result;
    
}


//--------------------------------------------------------------
void ofApp::setup(){
    
    
	udp.Create();
	udp.Bind(7777);
    udp.SetNonBlocking(true);
    
    
    
    
}



//--------------------------------------------------------------
void ofApp::update(){
    
    
	char udpMessage[sizeof(sparkyToOFPacket)];
    memset(udpMessage, 0, sizeof(sparkyToOFPacket));
    int nBytesRevd = udp.Receive(udpMessage, sizeof(sparkyToOFPacket));
    
    
	if(nBytesRevd == sizeof(sparkyToOFPacket)){
        bGotSth = true;
        
        cout << "got data" << endl;
        //check info
        memset(&S2Opacket, 0, sizeof(sparkyToOFPacket));
        memcpy(&S2Opacket, udpMessage, sizeof(sparkyToOFPacket));
        
        //time
        cout << S2Opacket.millisRunning << endl;
        
        //ip
        ip[0] = S2Opacket.ipSpark >> 24 & 0xFF;
        ip[1] = S2Opacket.ipSpark >> 16 & 0xFF;
        ip[2] = S2Opacket.ipSpark >> 8 & 0xFF;
        ip[3] = S2Opacket.ipSpark & 0xFF;
        cout << ip[0] << "." << ip[1]<< "." << ip[2]<< "."<< ip[3]<< endl;
        string tempIp = ofToString(ip[0]) + "." + ofToString(ip[1]) + "."
        + ofToString(ip[2]) + "." + ofToString(ip[3]);
        
        //uuid
        string uuid( S2Opacket.uuid, S2Opacket.uuid + sizeof S2Opacket.uuid / sizeof S2Opacket.uuid[0] );
        cout << uuid << endl;
        
        bool bDoesThisSparkExist = false;
        for (int i = 0; i < sparks.size(); i++){
            if (sparks[i].ip == tempIp){
                bDoesThisSparkExist = true;
            }
        }
        
        if (!bDoesThisSparkExist){
            spark temp;

            temp.udp.Create();
            temp.udp.Connect(tempIp.c_str(),8888);
            temp.udp.Bind(7777);
            temp.udp.SetNonBlocking(true);
            temp.ip = tempIp;
            temp.uuid = uuid;
            temp.millisAlive = S2Opacket.millisRunning;
            temp.nPacketsReceived++;
            cout << "create the first object " << tempIp << endl;
            
            sparks.push_back(temp);
            
        } else {
            
            for (int i = 0; i< sparks.size(); i++) {
                if(sparks[i].ip == tempIp){
                    sparks[i].readPacketFromSpark(udpMessage);
                    /*sparks[i].millisAlive = S2Opacket.millisRunning;
                    sparks[i].nPacketsReceived++;
                    sparks[i].getPacketBackTime = ofGetElapsedTimef();
                    sparks[i].deltaTimeRoundTrip = sparks[i].getPacketBackTime - sparks[i].sendPacketOutTime;*/
                }
            }
        }

    } else {
        
        bGotSth = false;
    }

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (bGotSth) ofBackground(255,0,0);
    else ofBackground(200);
    
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
    O2Spacket.time = ofGetElapsedTimef();
    O2Spacket.ofIp = getOfIpInt();
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



int ofApp::getOfIpInt(){
    
    string execReturn = exec("ifconfig | grep -E \"inet ([0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3})\" | awk \'{print $2}\'");
    
    vector <string> allIp = ofSplitString(execReturn, "\n");
    string localIp;
    
    // parsing works,, not sure if it would works in every case tho
    for (int i=0; i<allIp.size(); i++) {
        vector <string> ipBreakdown = ofSplitString(allIp[i],".");
        if (ipBreakdown[0] == "192") {
            localIp = allIp[i];
            break;
        }
        else if (ipBreakdown[0]!= "127") {
            localIp = allIp[i];
            break;
        }
    }
    
    vector<string> ipBreakdown = ofSplitString(localIp, ".");
    unsigned char a = ofToInt(ipBreakdown[0]);
    unsigned char b = ofToInt(ipBreakdown[1]);
    unsigned char c = ofToInt(ipBreakdown[2]);
    unsigned char d = ofToInt(ipBreakdown[3]);
    
    int addressAsInt = a << 24 | b << 16 | c << 8 | d;

    return addressAsInt;
}


string ofApp::convertIpToString(int ip){
    
    
    int temp[4];
    temp[0] = ip >> 24 & 0xFF;
    temp[1] = ip >> 16 & 0xFF;
    temp[2] = ip >> 8 & 0xFF;
    temp[3] = ip & 0xFF;
    cout << temp[0] << "." << temp[1]<< "." << temp[2]<< "."<< temp[3]<< endl;
    
    
    string tempIp = ofToString(temp[0]) + "." + ofToString(temp[1]) + "."
    + ofToString(temp[2]) + "." + ofToString(temp[3]);

    return tempIp;
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
