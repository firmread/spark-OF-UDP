#include "ofApp.h"


//--------------------------------------------------------------
bool sortSpark(const spark &a, const spark &b) {
    return a.boardNumber < b.boardNumber;
}

void ofApp::loadUUIDList(){
    ofBuffer buffer = ofBufferFromFile("uuidList.txt");
    string line;
    while (true){
        line = buffer.getNextLine();
        vector < string > str = ofSplitString(line, " ");
        uuidMapping[str[1]] = ofToInt(str[0]);
        if (buffer.isLastLine()) break;
    }
}


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetCircleResolution(100);
    
    
    getOfLocalIp readIp;
    myIPaddressInt = readIp.getInt();
    myIPaddressString = readIp.getString();
    vector < string > ipSplit = ofSplitString(myIPaddressString, ".");
    myIPadressJustFirstThree = "";
    for (int i = 0; i < 3; i++){
        myIPadressJustFirstThree += ipSplit[i] + ".";
    }
    
    
    
	udp.Create();
	udp.Bind(7777);
    udp.SetNonBlocking(true);
    //heart.setup(500);
    
    loadUUIDList();
    
    gui.setup();
    gui.add(useOsc.setup("use OSC", true));
    gui.add(sendColor.setup("send color data to lights", true));
    gui.add(flipRgb.setup("flip rgb to bgr on send", true));
    gui.add(setAllWhite.setup("set all white", false));
    gui.add(setAllBlack.setup("set all black", false));
    gui.add(setAllRandom.setup("set all random", false));

    gui.setPosition(500,70);
    
    receiver.setup(PORT);
    
    
    
    colorValuesForOutput.assign(50, ofColor(ofColor::gray));
    
}



//--------------------------------------------------------------
void ofApp::update(){
    
    
    if (ofGetFrameNum() % 2 == 0){
        fireDiscovery();
    }
    
    
    if (setAllWhite == true){
        setAllWhite = false;
        for (int i = 0; i < colorValuesForOutput.size(); i++){
            colorValuesForOutput[i] = ofColor::white;
        }
        //useOsc = false;
    }
    if (setAllBlack == true){
        setAllBlack = false;
        
        for (int i = 0; i < colorValuesForOutput.size(); i++){
            colorValuesForOutput[i] = ofColor::black;
        }
        //useOsc = false;
    }
    
    if (setAllRandom == true){
        setAllRandom = false;
        
        for (int i = 0; i < colorValuesForOutput.size(); i++){
            colorValuesForOutput[i] = ofColor(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255));;
        }
        //useOsc = false;
    }
    
    
    // OSC
    while(receiver.hasWaitingMessages()){
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        if(m.getAddress() == "/color"){
            
    //              :(  this is bad
    //            for (int i = 0; i < m.getNumArgs()/3; i++){
    //                colorValuesForOutput[i].set( m.getArgAsInt32(i*3+0), m.getArgAsInt32(i*3+1), m.getArgAsInt32(i*3+2));
    //            }
            
            for (int i = 0; i < m.getNumArgs(); i++){
                int value = m.getArgAsInt32(i);
                int red = value >> 24 & 0xFF; //hex FF = white (255) 1111 1111
                int green = value >> 16 & 0xFF;
                int blue = value >> 8 & 0xFF;
                colorValuesForOutput[i].set(red, green, blue);
                
            }
            
            
            
            
            
        }
    }
    
    
    
    if (sendColor){
        sendColorData();
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
                sparks[sparks.size()-1].boardNumber = uuidMapping[sparks[sparks.size()-1].uuid];
                ofSort(sparks, sortSpark);
                
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
    
//    if (ofGetMousePressed()){
//    
//        if (ofGetFrameNum() % 60 ==0){
//            fireControl();
//        }
//    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofBackgroundGradient(80, 0);
    string sparksNo = ofToString(sparks.size());

    for (int i =0; i< sparks.size(); i++){
        sparks[i].draw(100, 100+100*i);
    }
    
    
    ofDrawBitmapStringHighlight("conneting light control\n" + myIPaddressString, 500, 20);
    
    gui.draw();
    
    
    float width = ofGetWidth() / (float)colorValuesForOutput.size();
    for (int i = 0; i < colorValuesForOutput.size(); i++){
        
        
        ofSetColor(colorValuesForOutput[i]);
        ofFill();
        ofRect(i*width, ofGetHeight(), width-1, -30);
        
        if (colorValuesForOutput[i].getBrightness() < 10){
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
    
    
//    if (key == ' '){
//        fireDiscovery();
//    }
    
    if (key == 'c'){
        //fireControl();
        
    }
    
    
}

//--------------------------------------------------------------
void ofApp::fireDiscovery(){
    
    // TODO:  MULTICAST ???
    
    
    memset(&O2Spacket, 0, sizeof(ofToSparkyPacket));
    O2Spacket.packetType = PACKET_TYPE_DISCOVERY;
    
    O2Spacket.ofIp = myIPaddressInt;
    char packetBytes[sizeof(ofToSparkyPacket)];
    O2Spacket.ofPacketSentOutTime = ofGetElapsedTimef();
    memcpy(packetBytes, &O2Spacket, sizeof(ofToSparkyPacket));
    
    ofxUDPManager udp4discovery;
    udp4discovery.Create();
    udp4discovery.SetEnableBroadcast(true);
    udp4discovery.Connect("192.168.10.255", 8888);
    udp4discovery.Send(packetBytes,sizeof(ofToSparkyPacket));
    udp4discovery.Close();
    
    
    
//    for (int i = 0; i < 256; i++){
//        
//        string IP = myIPadressJustFirstThree + ofToString(i);
//        
//        bool bFoundAlready = false;
//        for (int j = 0; j < sparks.size(); j++){
//            if (sparks[j].ip == IP){
//                bFoundAlready = true;
//            }
//        }
//        
//        if (!bFoundAlready){
//            udp4discovery.Create();
//            udp4discovery.Connect(IP.c_str(),8888);
//            udp4discovery.SetNonBlocking(false);
//            udp4discovery.Send(packetBytes,sizeof(ofToSparkyPacket));
//            //ofSleepMillis(30);
//        }
//    }
    

}
//--------------------------------------------------------------
void ofApp::sendColorData(){
    
    
    memset(&O2Spacket, 0, sizeof(ofToSparkyPacket));
    O2Spacket.packetType = PACKET_TYPE_COLOR;
    O2Spacket.ofPacketSentOutTime = ofGetElapsedTimef();

    O2Spacket.ofIp = myIPaddressInt;
    char packetBytes[sizeof(ofToSparkyPacket)];
    
    for (int i=0; i<sparks.size(); i++) {
        
        int number = sparks[i].boardNumber;
        ofColor colorToSend = colorValuesForOutput[number];
        

        if (flipRgb){
            O2Spacket.r = colorToSend.b;
            O2Spacket.g = colorToSend.g;
            O2Spacket.b = colorToSend.r;
        } else {
            O2Spacket.r = colorToSend.r;
            O2Spacket.g = colorToSend.g;
            O2Spacket.b = colorToSend.b;
        }
        
        memcpy(packetBytes, &O2Spacket, sizeof(ofToSparkyPacket));
        
    
        sparks[i].udp.Create();
        sparks[i].udp.Connect(sparks[i].ip.c_str(), 8888);
        int sent = sparks[i].udp.Send(packetBytes, sizeof(ofToSparkyPacket));
        sparks[i].udp.Close();
        
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
