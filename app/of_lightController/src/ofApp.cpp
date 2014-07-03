#include "ofApp.h"
#include "sparkPacketUtils.h"

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
    ofSetCircleResolution(20);
    
    
    getOfLocalIp readIp;
    myIPaddressInt = readIp.getInt();
    myIPaddressString = readIp.getString();
    vector < string > ipSplit = ofSplitString(myIPaddressString, ".");
    myIPadressJustFirstThree = "";
    
    if (ipSplit.size() == 4){
        for (int i = 0; i < 3; i++){
            myIPadressJustFirstThree += ipSplit[i] + ".";
        }
    } else {
        myIPadressJustFirstThree = "0.0.0.";
    }
    
    
	udp.Create();
	udp.Bind(7777);
    udp.SetNonBlocking(true);
    heart.setup(200);
    colorTimer.setup( (int)((1.0/80.0) * 1000.0));
    
    loadUUIDList();
    
    gui.setup();
    
    gui.add(useOsc.setup("use OSC", true));
    
    gui.add(heartbeatFrameRate.setup("heartbeat (fps)", 2, 0.1, 100));
    gui.add(colorFrameRate.setup("color (fps)", 30, 0.1, 100));
    gui.add(interpolateRate.setup("interpolate speed", 1000, 0, 3000));
    gui.add(verticalSync.setup("vertical sync", false));
    

    
    gui.add(sendColor.setup("send color data", true));
    gui.add(sendHeartbeat.setup("send hearbeat data", true));
    gui.add(sendOneHeartbeat.setup("send one hearbeat", true));
    gui.add(flipRgb.setup("flip rgb to bgr on send", true));
    gui.add(setAllWhite.setup("set all white", false));
    gui.add(setAllBlack.setup("set all black", false));
    gui.add(setAllRed.setup("set all red", false));
    gui.add(setAllBlue.setup("set all blue", false));
    gui.add(setAllGreen.setup("set all green", false));
    gui.add(setAllRandom.setup("set all random", false));
    
    
    preferGuiPos.set(ofGetWidth()*3/4, 70);
    gui.setPosition(preferGuiPos);
    
    receiver.setup(PORT);
    
    
    
    colorValuesForOutput.assign(50, ofColor(ofColor::gray));
    
    //ofSetVerticalSync(false);
    //ofSetFrameRate(60);
    
}


bool bLastSync = false;

//--------------------------------------------------------------
void ofApp::update(){
    
    
    
    heart.setTimer((int)((1.0/heartbeatFrameRate) * 1000.0));
    colorTimer.setTimer((int)((1.0/colorFrameRate) * 1000.0));
    

    if (bLastSync != verticalSync){
        ofSetVerticalSync(verticalSync);
    }
    bLastSync =verticalSync;
    
    
    
    heart.update(ofGetElapsedTimeMillis());
    if (heart.bTimerFired() && sendHeartbeat){
        
        for (int i = 0; i < sparks.size(); i++){
            sparks[i].bSendHeartBeat = true;
        }
    }
    
    if (sendOneHeartbeat == true){
        sendOneHeartbeat = false;
        for (int i = 0; i < sparks.size(); i++){
            sparks[i].bSendHeartBeat = true;
        }
    }
    
    colorTimer.update(ofGetElapsedTimeMillis());
        if (colorTimer.bTimerFired() && sendColor){
            sendColorData();
        }
    
    
    //if (ofGetFrameNum() % 100 == 0){
    //    fireDiscovery();
    //}
    
    
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
    
    if (setAllRed == true){
        setAllRed = false;
        for (int i = 0; i < colorValuesForOutput.size(); i++){
            colorValuesForOutput[i] = ofColor::red;
        }
    }
    
    if (setAllBlue == true){
        setAllBlue = false;
        for (int i = 0; i < colorValuesForOutput.size(); i++){
            colorValuesForOutput[i] = ofColor::blue;
        }
    }
    
    if (setAllGreen == true){
        setAllGreen = false;
        for (int i = 0; i < colorValuesForOutput.size(); i++){
            colorValuesForOutput[i] = ofColor::green;
        }
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
    
    
    
//    if (sendColor && ofGetFrameNum() % 2 == 0){
//        sendColorData();
//    }
    
	char udpMessage[sizeof(sparkyToOFPacket)];
    memset(udpMessage, 0, sizeof(sparkyToOFPacket));
    
    
    bool bAnyAvailable = true;
    
    while (bAnyAvailable == true){
        int nBytesRevd = udp.Receive(udpMessage, sizeof(sparkyToOFPacket));
        
        if (nBytesRevd <= 0) bAnyAvailable = false;
        
        
        if(nBytesRevd == sizeof(sparkyToOFPacket)){
            bGotSth = true;
            
            // this is imporant, I don't think we should time against all this junk here.
            
            float receivedTime = ofGetElapsedTimef();
            memset(&S2Opacket, 0, sizeof(sparkyToOFPacket));
            memcpy(&S2Opacket, udpMessage, sizeof(sparkyToOFPacket));
            
            string ipThisPacket = ipFromInt( S2Opacket.ipSpark);
            
            //packetHandler ph(S2Opacket);
            
            bool bDoesThisSparkExist = false;
            for (int i = 0; i < sparks.size(); i++){
                if (sparks[i].ip == ipThisPacket ){
                    //cout << "ph.ipSparkString : " << i << " : " << sparks[i].ip << endl;
                    bDoesThisSparkExist = true;
                }
            }
            
            
            
            // register it if we never seen it before
            if (!bDoesThisSparkExist){
                
                spark temp;
                sparks.push_back(temp);
                sparks[sparks.size()-1].setup(S2Opacket);
                sparks[sparks.size()-1].boardNumber = uuidMapping[sparks[sparks.size()-1].uuid];
                ofSort(sparks, sortSpark);
                
            // otherwise, welcome back our beloved sparky!  !
            } else {
                
                
                
                for (int i = 0; i< sparks.size(); i++) {
                    if(sparks[i].ip == ipThisPacket ){
                       sparks[i].readPacketFromSpark(S2Opacket, receivedTime);
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

//    for (int i =0; i< sparks.size(); i++){
//        sparks[i].draw(100, 100+100*i);
//    }
        for (int i =0; i< sparks.size(); i++){
            
            // wraping over //
            // start new column when exceed screen height
            ofPoint pos(50, 50+60*i);
            while (pos.y > ofGetHeight()-100) {
                pos.x += 280;
                pos.y -= ofGetHeight()-150;
            }
            
            sparks[i].drawSmall(pos.x, pos.y);
            
        }
    
    
    
    ofDrawBitmapStringHighlight("Connecting Lights control panel\n" + myIPaddressString,
                                preferGuiPos.x,
                                preferGuiPos.y-50);
    
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
    
    
    if (key == ' '){
        fireDiscovery();
    }
    
    if (key == 'c'){
        //fireControl();
    }
    
    if (key == 'f'){
        ofToggleFullscreen();
        preferGuiPos.set(ofGetWidth()*3/4, 70);
        gui.setPosition(preferGuiPos);
    }
    
    
}

//--------------------------------------------------------------
void ofApp::fireDiscovery(){
    
    // TODO:  MULTICAST ???
    
    cout << "firing discovery" << endl;
    memset(&O2Spacket, 0, sizeof(ofToSparkyPacket));
    O2Spacket.packetType = PACKET_TYPE_DISCOVERY;
    
    O2Spacket.ofIp = myIPaddressInt;
    char packetBytes[sizeof(ofToSparkyPacket)];
    O2Spacket.ofPacketSentOutTime = ofGetElapsedTimef();
    memcpy(packetBytes, &O2Spacket, sizeof(ofToSparkyPacket));
    
//    udp4discovery.Create();
//    udp4discovery.SetEnableBroadcast(true);
//    udp4discovery.SetNonBlocking(false);
//    udp4discovery.Connect("192.168.10.255", 8888);
//    
//    udp4discovery.Send(packetBytes,sizeof(ofToSparkyPacket));
//    udp4discovery.Close();
//
//    
//    
    for (int i = 2; i < 254; i++){
        
        string IP = myIPadressJustFirstThree + ofToString(i);
        
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
            //ofSleepMillis(1);
        }
    }
    

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
        
        O2Spacket.transitionTime = interpolateRate;
        
        
        O2Spacket.packetCount = sparks[i].sparkSentCount++;
        
        
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
